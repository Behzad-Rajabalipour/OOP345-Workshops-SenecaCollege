#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Station.h"
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;
using namespace sdds;

// Function template to load data from a file into a vector of a given type T
template<typename T>
static void loadFromFile(const char*, vector<T>&);

int main(int argc, char** argv)
{
    // Command-line information
    cout << "Command Line: " << argv[0];
    for (int i = 1; i < argc; i++)
        cout << " " << argv[i];
    cout << endl << endl;

    // Check for the correct number of command-line arguments
    if (argc < 4) {
        cerr << "ERROR: Insufficient number of arguments\n";
        return 1;
    }

    // Vectors to store instances of Station and CustomerOrder
    vector<Station> theStations;
    vector<CustomerOrder> theOrders;

    // Milestone 1
    {
        try
        {
            // Set the delimiter and load data into theStations vector from two input files
            Utilities::setDelimiter(',');
            loadFromFile<Station>(argv[1], theStations);
            Utilities::setDelimiter('|');
            loadFromFile<Station>(argv[2], theStations);
        }
        catch (const string& err)
        {
            cerr << err << '\n';
            exit(2);
        }

        // Display Station information
        cout << "========================================" << endl;
        cout << "=         Stations (summary)           =" << endl;
        cout << "========================================" << endl;
        for (Station& station : theStations)
            station.display(cout, false);
        cout << endl << endl;

        cout << "========================================" << endl;
        cout << "=          Stations (full)             =" << endl;
        cout << "========================================" << endl;
        for (Station& station : theStations)
            station.display(cout, true);
        cout << endl << endl;

        // Select a Station object and verify its functionality
        cout << "========================================" << endl;
        cout << "=          Manual Validation           =" << endl;
        cout << "========================================" << endl;
        cout << "getItemName(): " << theStations[0].getItemName() << endl;
        cout << "getNextSerialNumber(): " << theStations[0].getNextSerialNumber() << endl;
        cout << "getNextSerialNumber(): " << theStations[0].getNextSerialNumber() << endl;
        cout << "getQuantity(): " << theStations[0].getQuantity() << endl;
        theStations[0].updateQuantity();
        cout << "getQuantity(): " << theStations[0].getQuantity() << endl;
        cout << endl << endl;

        cout << "========================================" << endl;
        cout << "=              Utilities               =" << endl;
        cout << "========================================" << endl;
        // Create & initialize an array of input data
        const struct { char delim; std::string data; } input[]
        {
            { 'a', "a"},
            { 'b', "a" },
            { 'l', "Hello"},
            { ',', "apple,orange,banana,kiwi,strawberry,yellow watermelon" },
            { '|', "Gengar|Arcanine|Bulbasaur|Blaziken|C h a r i z a r d|Umbreon|Lucario|Eevee"}
        };

        for (auto& item : input)
        {
            Utilities::setDelimiter(item.delim);
            Utilities util;
            bool more = true; // If there are more tokens in the input string
            size_t pos = 0u; // Position of the next token in the input string
            cout << "Data: [" << item.data << "]    Delimiter: [" << item.delim << "]\n";
            while (more)
            {
                try
                {
                    auto token = util.extractToken(item.data, pos, more);
                    cout << "   Token: [" << token << "] [" << util.getFieldWidth() << "]\n";
                }
                catch (...) { cout << "   ERROR: No token.\n"; }
            }
        }
    }

    // Milestone 2
    {
        // Load CustomerOrder data from the specified file
        loadFromFile<CustomerOrder>(argv[3], theOrders);

        // Display CustomerOrder information
        cout << "========================================" << endl;
        cout << "=                Orders                =" << endl;
        cout << "========================================" << endl;
        for (CustomerOrder& order : theOrders)
            order.display(std::cout);
        cout << endl << endl;

        // Select a CustomerOrder object and verify its functionality
        cout << "========================================" << endl;
        cout << "=          Manual Validation           =" << endl;
        cout << "========================================" << endl;
        cout << "CustomerOrders::display(): "; // Test #1
        theOrders[theOrders.size() - 1].display(cout);
        cout << endl;

        try
        {
            // Copy constructor
            cout << "CustomerOrders::CustomerOrders(&): "; // Test #2
            CustomerOrder anOrder(theOrders[0]);
        }
        catch (...)
        {
            cout << "----> ERROR: Cannot make copies.";
            cout << endl << endl;
        }

        // Move constructor
        cout << "CustomerOrders::CustomerOrders(&&): "; // Test #3
        CustomerOrder tmp(std::move(theOrders[theOrders.size() - 1]));
        theOrders.pop_back();
        tmp.display(cout);
        cout << endl;

        // Creating a CustomerOrder from a string
        cout << "CustomerOrders::CustomerOrders(string): "; // Test #4
        string strRecord = "Chloe/Flight PC/CPU/GPU/Power Supply";
        Utilities::setDelimiter('/');
        CustomerOrder tmp2(strRecord);
        tmp2.display(cout);
        cout << endl;

        // Move assignment operator
        cout << "CustomerOrders::operator=(&&): "; // Test #5
        tmp2 = std::move(theOrders[theOrders.size() - 1]);
        theOrders.pop_back();
        tmp2.display(cout);
        cout << endl;

        // CustomerOrder functionality tests
        cout << "CustomerOrders::fillItem()" << endl; // Test #6
        cout << "isOrderFilled(): "
            << (tmp2.isOrderFilled() ? "FILLED" : "MISSING")
            << endl;

        tmp2.fillItem(theStations[0], cout);
        cout << "isItemFilled(\"CPU\"): "
            << (tmp2.isItemFilled("CPU") ? "FILLED" : "MISSING")
            << endl;

        cout << "isOrderFilled(): "
            << (tmp2.isOrderFilled() ? "FILLED" : "MISSING")
            << endl;

        for (size_t i = 0; i < theStations.size(); i++)
            tmp2.fillItem(theStations[i], cout);  // tmp2 is a CustomerOrder

        cout << "isOrderFilled(): "
            << (tmp2.isOrderFilled() ? "FILLED" : "MISSING")
            << endl;
    }

    return 0;
}

// Function template definition to load data from a file into a vector of a given type T
template<typename T>
static void loadFromFile(const char* filename, vector<T>& theCollection)
{
    ifstream file(filename);
    if (!file)
        throw string("Unable to open [") + filename + "] file.";

    string record;
    while (!file.eof())
    {
        std::getline(file, record);
        T elem(record);  // Type T can be either CustomerOrder or Station since both have a constructor that takes string&
        theCollection.push_back(std::move(elem));  // Create a list, each item of which is a line from CustomerOrder.txt or Stations2.txt
    }

    file.close();
}
