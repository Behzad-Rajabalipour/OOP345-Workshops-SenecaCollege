#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>
#include <stdexcept> // For error handling, e.g., invalid_argument. #ref1

using namespace std;

namespace sdds {
    // Initialize static members outside the class definition
    size_t Station::m_widthField{ 0 };
    int Station::id_generator = 0;

    // Constructor that takes a record string as an argument
    Station::Station(const string& record) {
        bool more = true;
        size_t next_pos = 0;
        Utilities util; // Create a Utilities object for token extraction

        try {
            // Extract information from the record string
            m_itemName = util.extractToken(record, next_pos, more);
            m_serialNumber = stoi(util.extractToken(record, next_pos, more));
            m_quantity = stoi(util.extractToken(record, next_pos, more));

            // Check if there is more information (description)
            if (more) {
                m_description = util.extractToken(record, next_pos, more);

                // Remove leading whitespaces from m_description
                size_t start = m_description.find_first_not_of(" ");
                m_description = (start == string::npos) ? m_description : m_description.substr(start);
            }

            // Update the widthField if necessary
            if (Station::m_widthField < m_itemName.length()) {
                Station::m_widthField = m_itemName.length();
            }

            m_id = ++id_generator; // Increment the id_generator for a unique ID
        }
        catch(const invalid_argument& err) { // Catch invalid_argument exceptions. #ref1
            cerr << "Error: " << err.what() << endl; // Print the error message to cerr (standard error)
            // Note: The constructor continues execution even after an exception is caught,
            // so an object may be partially initialized if an exception occurs.
        }
    }

    // Getter function to return the item name
    const string& Station::getItemName() const {
        return m_itemName;
    }

    // Function to get the next serial number and increment it
    size_t Station::getNextSerialNumber(){
        return m_serialNumber++;
    }

    // Getter function to return the quantity
    size_t Station::getQuantity() const {
        return m_quantity;
    }

    // Function to update the quantity (decrement by 1)
    void Station::updateQuantity() {
        if (m_quantity > 0)
            --m_quantity;
    }

    // Function to display station information
    void Station::display(ostream& os, bool full) const {
        os << setw(3) << right << setfill('0') << m_id << " | "
            << left << setw(m_widthField) << setfill(' ') << m_itemName << "| "
            << right << setw(6) << setfill('0') << m_serialNumber << " | ";
        if (full) {
            os << setw(4) << setfill(' ') << m_quantity << " | " << m_description;
        }
        os << endl;
    }
}
