#include "Station.h"
#include "Utilities.h"              // Include the declaration of Utilities
#include <iostream>
#include <iomanip>
#include <stdexcept>                // Include <stdexcept> for exception handling 

using namespace std;

namespace sdds {
    // Static member initialization
    size_t Station::m_widthField{ 0 };     // Width field shared among all Station objects
    int Station::id_generator = 0;          // Generator for unique IDs

    // Constructor that initializes the Station object with the information from the record
    Station::Station(const string& record) {
        bool more = true;
        size_t next_pos = 0;
        Utilities util;                   // Create an instance of Utilities to tokenize the record

        try {
            // Extract information from the record
            m_itemName = util.extractToken(record, next_pos, more);
            m_serialNumber = stoi(util.extractToken(record, next_pos, more));
            m_quantity = stoi(util.extractToken(record, next_pos, more));

            // If there is more data in the record, extract the description
            if (more) {
                m_description = util.extractToken(record, next_pos, more);
            }

            // Update the static widthField if necessary
            if (Station::m_widthField < m_itemName.length()) {
                Station::m_widthField = m_itemName.length();
            }

            // Assign a unique ID to the station
            m_id = ++id_generator;
        }
        catch (const invalid_argument& err) {  // Handle invalid argument exceptions 
            cerr << "Error: " << err.what() << endl;  // Display the error message using cerr
        }
    }

    // Accessor member function to get the name of the item
    const string& Station::getItemName() const {
        return m_itemName;
    }

    // Member function to get the next serial number and increment it
    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    // Accessor member function to get the quantity of the item
    size_t Station::getQuantity() const {
        return m_quantity;
    }

    // Member function to update the quantity (decrement by 1)
    void  Station::updateQuantity() {
        if (m_quantity > 0)
            --m_quantity;
    }

    // Member function to display the station information
    void Station::display(ostream& os, bool full) const {
        os << setw(3) << right << setfill('0') << m_id << " | "
            << left << setw(m_widthField) << setfill(' ') << m_itemName << " | "
            << right << setw(6) << setfill('0') << m_serialNumber << " | ";

        // Display additional information if 'full' is true
        if (full) {
            os << setw(4) << setfill(' ') << m_quantity << " | " << m_description;
        }
        os << endl;
    }

}  // namespace sdds
