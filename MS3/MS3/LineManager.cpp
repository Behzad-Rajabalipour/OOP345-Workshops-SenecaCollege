#include "LineManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>		// For runtime_error.
#include <map>				// For using map container.

using namespace std;
using namespace sdds;

deque<CustomerOrder> g_pending;		// Defined in Workstation.h 

namespace sdds {
    // LineManager initializes the workstations in the assembly line and sets up the order of processing.
    LineManager::LineManager(const string& file, vector<Workstation*>& workstations) {
        // Attempt to open the file
        ifstream inFile(file);
        if (!inFile) throw runtime_error("Cannot open file.");  // Throw a runtime error if the file cannot be opened.

        // Initialize the count of customer orders from the pending orders
        m_cntCustomerOrder = g_pending.size();  // g_pending is a vector<CustomerOrder>.

        // Create a map to associate each workstation's item name with its corresponding workstation object. 
        map<string, Workstation*> wsMap;
        for (auto& ws : workstations) {
            wsMap[ws->getItemName()] = ws;  // Workstation map, associates the name of each station with its object. For example: workstation[Desk] = object of that workstation.
        }

        // Read the AssemblyLine.txt file to determine the next workstation for each workstation
        string line, current, next;
        while (getline(inFile, line)) {
            istringstream record(line);
            if (getline(record, current, '|')) {  // For example: Desk|Office Chair => current = Desk, next = Office Chair
                if (!getline(record, next))
                    next = "";
                wsMap[current]->setNextStation(wsMap[next]);  // Set the next station for each workstation based on the information in the file.
                m_activeLine.push_back(wsMap[current]);
            }
        }

        // Check if any workstation is the last workstation for another
        for (auto& ws : workstations) {
            if (find_if(workstations.begin(), workstations.end(), [&ws](Workstation* ws_sample) {
                return ws_sample->getNextStation() == ws;
                }) == workstations.end()) {
                m_firstWS = ws;
                break;
            }
        }
    }

    // Reorder workstations based on the next station relationships
    void LineManager::reorderStations() {
        // Traverse the workstations and populate m_activeLine in the correct order
        auto currentWS = m_firstWS;
        m_activeLine.clear();
        while (currentWS) {
            m_activeLine.push_back(currentWS);
            currentWS = currentWS->getNextStation();
        }
    }

    // Execute one cycle of the assembly line
    bool LineManager::run(ostream& os) {
        static size_t count = 0;
        os << "Line Manager Iteration: " << ++count << endl;

        // If there are pending orders, move the first order to the first workstation
        if (!g_pending.empty()) {
            *m_firstWS += move(g_pending.front());  // Move the data in its memory location, but does not delete the object.
            g_pending.pop_front();
        }

        // Fill items for each workstation
        for (auto& ws : m_activeLine) {
            ws->fill(os);
        }

        // Attempt to move orders between workstations
        for (auto& ws : m_activeLine) {
            ws->attemptToMoverOrder();
        }

        // Check if all customer orders have been completed or are incomplete
        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }

    // Display the status of each workstation in the assembly line
    void LineManager::display(ostream& os) const {
        for (const auto& workStation : m_activeLine) {
            workStation->display(os);
        }
    }
}
