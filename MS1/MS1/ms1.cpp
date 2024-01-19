#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Station.h"
#include "Utilities.h"

using namespace std;
using namespace sdds;

// Function prototype for loading stations from a file
static bool loadStations(const char*, vector<Station>&);

int main(int argc, char** argv)
{
    // Display the command line arguments
    cout << "Command Line: " << argv[0];
    for (int i = 1; i < argc; i++)
        cout << " " << argv[i];
    cout << endl << endl;
    // Check if there are enough command line arguments
    if (argc < 3) {
        cerr << "ERROR: Insufficient number of arguments\n";
        return 1;
    }

    //**************//
    vector<Station> theStations;
    try
    {
        // Set the delimiter and load stations from the first file
        Utilities::setDelimiter(',');
        loadStations(argv[1], theStations);

        // Reset the delimiter and load stations from the second file
        Utilities::setDelimiter('|');
        loadStations(argv[2], theStations);
    }
    catch (const string& err)
    {
        cerr << err << '\n';
        exit(2);
    }

    // Display summary information of stations
    cout << "========================================" << endl;
    cout << "=         Stations (summary)           =" << endl;
    cout << "========================================" << endl;
    for (Station& theItem : theStations)
        theItem.display(cout, false);
    cout << endl << endl;

    // Display full information of stations
    cout << "========================================" << endl;
    cout << "=          Stations (full)             =" << endl;
    cout << "========================================" << endl;
    for (Station& theItem : theStations)
        theItem.display(cout, true);
    cout << endl << endl;

    // Validate station functionality
    cout << "========================================" << endl;
    cout << "=          Manual Validation           =" << endl;
    cout << "========================================" << endl;
    cout << "getItemName(): " << theStations[0].getItemName() << endl;
    cout << "getNextSerialNumber(): " << theStations[0].getNextSerialNumber() << endl;
    cout << "getNextSerialNumber(): " << theStations[0].getNextSerialNumber() << endl;
    cout << "getQuantity(): " << theStations[0].getQuantity() << endl;
    theStations[0].updateQuantity();
    cout << "getQuantity(): " << theStations[0].getQuantity() << endl;
    cout << endl;

    // Utilize Utilities class to extract tokens
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
        Utilities::setDelimiter(item.delim); // Set the delimiter. 
        Utilities util;
        bool more = true; // Flag indicating whether there are more tokens
        size_t pos = 0u; // Starting position for extracting tokens from the data
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

    return 0;
}

// Load stations from a file into the vector
bool loadStations(const char* filenameSt, vector<Station>& theStations)
{
    ifstream file(filenameSt);
    if (!file)
        throw string("Unable to open [") + filenameSt + "] file";

    // Read each line from the file and create a Station object
    string theRecord;
    while (!file.eof()) // Continue until the end of the file
    {
        getline(file, theRecord);
        Station newItem(theRecord);
        theStations.push_back(std::move(newItem)); // Move the newly created item to the vector
    }
    file.close();
    return true;
}
