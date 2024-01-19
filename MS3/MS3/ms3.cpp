// Final Project
// Milestone 3
// ms3_prof.cpp
// Winter 2021
// Chris Szalwinski

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"
#include "Workstation.h"
#include "LineManager.h"

using namespace std;
using namespace sdds;

// Function template to load data from file into vector
template<typename T>
static void loadFromFile(const char*, vector<T>&);

// Function template to load data from file into vector of pointers
template<typename T>
static void loadFromFile(const char*, vector<T*>&);

int main(int argc, char** argv)
{
    // Display command line arguments
    cout << "Command Line: " << argv[0];
    for (int i = 1; i < argc; i++)
        cout << " " << argv[i];
    cout << endl << endl;

    // Check if the correct number of command line arguments is provided
    if (argc != 5) {
        cerr << "ERROR: Incorrect number of arguments\n";
        return 1;
    }

    // Vector to store Workstation objects
    vector<Workstation*> theStations;
    // Vector to store CustomerOrder objects
    vector<CustomerOrder> theOrders;

    try {
        // Set delimiter to ',' and load Workstation data from the first file
        Utilities::setDelimiter(',');
        loadFromFile(argv[1], theStations);
        // Set delimiter to '|' and load additional Workstation data from the second file
        Utilities::setDelimiter('|');
        loadFromFile(argv[2], theStations);

        // Display summary of Stations
        cout << "========================================" << endl;
        cout << "=         Stations (summary)           =" << endl;
        cout << "========================================" << endl;
        for (const auto* station : theStations)
            station->Station::display(cout, false);
        cout << endl << endl;

        // Display full information of Stations
        cout << "========================================" << endl;
        cout << "=          Stations (full)             =" << endl;
        cout << "========================================" << endl;
        for (const auto* station : theStations)
            station->Station::display(cout, true);
        cout << endl << endl;

        // Manual validation of Station functionality
        cout << "========================================" << endl;
        cout << "=          Manual Validation           =" << endl;
        cout << "========================================" << endl;
        cout << "getItemName(): " << theStations[0]->getItemName() << endl;
        cout << "getNextSerialNumber(): " << theStations[0]->getNextSerialNumber() << endl;
        cout << "getNextSerialNumber(): " << theStations[0]->getNextSerialNumber() << endl;
        cout << "getQuantity(): " << theStations[0]->getQuantity() << endl;
        theStations[0]->updateQuantity();
        cout << "getQuantity(): " << theStations[0]->getQuantity() << endl;
        cout << endl << endl;

        // Load CustomerOrder data from the third file
        loadFromFile<CustomerOrder>(argv[3], theOrders);

        // Display CustomerOrders
        cout << "========================================" << endl;
        cout << "=                Orders                =" << endl;
        cout << "========================================" << endl;
        for (auto& order : theOrders) {
            order.display(std::cout);
            g_pending.push_back(std::move(order));
        }
        cout << endl << endl;

        // Display Stations (loaded)
        cout << "========================================" << endl;
        cout << "=       Display Stations (loaded)      =" << endl;
        cout << "========================================" << endl;
        LineManager lm(argv[4], theStations);
        lm.display(cout);
        cout << endl << endl;

        // Display Stations (ordered)
        cout << "========================================" << endl;
        cout << "=      Display Stations (ordered)      =" << endl;
        cout << "========================================" << endl;
        lm.reorderStations();
        lm.display(cout);
        cout << endl << endl;

        // Fill CustomerOrders in the assembly line until all orders are processed
        cout << "========================================" << endl;
        cout << "=           Filling Orders             =" << endl;
        cout << "========================================" << endl;
        while (!lm.run(cout));
        cout << endl << endl;
    }
    catch (const string& msg) {
        // Handle exceptions and display error message
        cerr << msg << '\n';
        return 2;
    }

    // Display processed complete orders
    cout << "========================================" << endl;
    cout << "=      Processed Orders (complete)     =" << endl;
    cout << "========================================" << endl;
    for (const auto& o : g_completed)
        o.display(cout);
    cout << endl << endl;

    // Display processed incomplete orders
    cout << "========================================" << endl;
    cout << "=     Processed Orders (incomplete)    =" << endl;
    cout << "========================================" << endl;
    for (const auto& o : g_incomplete)
        o.display(cout);
    cout << endl << endl;

    // Display full inventory of Stations
    cout << "========================================" << endl;
    cout << "=          Inventory (full)            =" << endl;
    cout << "========================================" << endl;
    for (const Station* theItem : theStations)
        theItem->display(cout, true);
    cout << endl;

    // Cleanup - delete allocated Workstation objects
    for (auto station : theStations)
        delete station;

    return 0;
}

// Function template to load data from file into vector
template<typename T>
static void loadFromFile(const char* filename, vector<T>& theCollection)
{
    // Validate filename
    if (!filename) {
        throw string("ERROR: No filename provided.");
    }

    // Open file
    ifstream file(filename);
    if (!file)
        throw string("Unable to open [") + filename + "] file.";

    // Read records from file
    string record;
    while (!file.eof())
    {
        std::getline(file, record);
        T elem(record);
        theCollection.push_back(std::move(elem));
    }

    // Close file
    file.close();
}

// Function template to load data from file into vector of pointers
template<typename T>
static void loadFromFile(const char* filename, vector<T*>& theCollection)
{
    // Validate filename
    if (!filename) {
        throw string("ERROR: No filename provided.");
    }

    // Open file
    ifstream file(filename);
    if (!file)
        throw string("Unable to open [") + filename + "] file.";

    // Read records from file
    string record;
    while (!file.eof())
    {
        std::getline(file, record);
        theCollection.push_back(new T(record));
    }

    // Close file
    file.close();
}
