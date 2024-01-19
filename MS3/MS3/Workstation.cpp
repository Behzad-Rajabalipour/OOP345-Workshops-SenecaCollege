#include <iostream>
#include <string>
#include "Station.h"
#include "Workstation.h"

using namespace std;

deque<sdds::CustomerOrder> g_completed;          // Storing completed CustomerOrders.
deque<sdds::CustomerOrder> g_incomplete;        // Storing incomplete CustomerOrders.

namespace sdds {

    // Constructor initializes the Workstation based on the station name
    Workstation::Workstation(const string& station) : Station(station), m_nextWorkStation(nullptr) {};

    // Attempt to fill the current station's first customer order
    void Workstation::fill(ostream& os) {
        // Check if there are customer orders in the queue
        if (!m_customersOrders.empty()) {
            // Fill the first item of the first customer order
            m_customersOrders.front().fillItem(*this, os);            // *this represents the current Workstation. calling fillItem() member function of CustomerOrder
        }
    }

    // Attempt to move the first customer order to the next station
    bool Workstation::attemptToMoverOrder() {
        if (m_customersOrders.empty()) return false;

        // Check if the item in the first customer order is filled or the station's quantity is 0
        if (m_customersOrders.front().isItemFilled(getName()) || getQuantity() == 0) {
            // Move the first customer order to the next station
            if (m_nextWorkStation) {
                m_nextWorkStation->m_customersOrders.push_back(move(m_customersOrders.front()));     // Move the first customer order to the next station's queue
            }
            else {
                // Check if the order is filled or incomplete and move it to the corresponding deque
                if (m_customersOrders.front().isOrderFilled())
                    g_completed.push_back(move(m_customersOrders.front()));            // Move the completed order to the completed deque
                else {
                    g_incomplete.push_back(move(m_customersOrders.front()));          // Move the incomplete order to the incomplete deque
                }
            }
            m_customersOrders.pop_front();             // Remove the first customer order from the current station's queue
            return true;
        }
        return false;
    }

    // Set the next station for the current station
    void Workstation::setNextStation(Workstation* station) {
        m_nextWorkStation = station;
    }

    // Get the next station of the current station
    Workstation* Workstation::getNextStation() const {
        return m_nextWorkStation;
    }

    // Display the current and next station names
    void Workstation::display(ostream& os) const {
        os << getItemName() << " --> "                     // Display the current station name
            << (m_nextWorkStation ? m_nextWorkStation->getItemName() : "End of Line") << endl;        // Display the next station name or "End of Line" if there is no next station
    }

    // Add a new customer order to the current station's queue
    Workstation& Workstation::operator+=(CustomerOrder&& CusOrder) {            
        m_customersOrders.push_back(move(CusOrder));            // Move the new customer order to the current station's queue
        return *this;
    }

}  // namespace sdds
