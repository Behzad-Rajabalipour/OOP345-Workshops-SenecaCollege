#include "Station.h"
#include "Utilities.h"              // Including the Utilities header for using its functionality
#include <iostream>
#include <iomanip>
#include <stdexcept>                // Including the necessary header for handling errors, like invalid_argument

using namespace std;

namespace sdds {
    // Static member initialization
    size_t Station::m_widthField{ 0 };   // Initializing the static member m_widthField. It represents the maximum width for display.
    int Station::id_generator = 0;

    // Constructor initializes the station based on the record string
    Station::Station(const string& record) {
        bool more = true;
        size_t next_pos = 0;
        Utilities util;       // Creating a Utilities object for token extraction.

        try {
            // Extracting information from the record string
            m_itemName = util.extractToken(record, next_pos, more);    // Extracting the item name. Using m_delimiter, which is a static member
            m_serialNumber = stoi(util.extractToken(record, next_pos, more));  // Extracting the serial number
            m_quantity = stoi(util.extractToken(record, next_pos, more));     // Extracting the quantity

            // If more tokens are available, extract the description
            if (more) {
                m_description = util.extractToken(record, next_pos, more);
            }

            // Update m_widthField if the current item name length is greater
            // Updating m_widthField to the maximum length of item names.
            if (Station::m_widthField < m_itemName.length()) {          
                Station::m_widthField = m_itemName.length();
            }

            // Set the station's unique ID using the id_generator
            m_id = ++id_generator;   // Assigning a unique ID to the station using the id_generator
        }
        catch (const invalid_argument& err) {            // Catching invalid_argument exceptions and displaying an error message.
            cerr << "Error: " << err.what() << endl;                   // Using cerr for error output
        }
    }

    // Get the item name of the station
    const string& Station::getItemName() const {
        return m_itemName;
    }

    // Get the next serial number for the station and increment the internal counter
    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    // Get the current quantity of items in the station
    size_t Station::getQuantity() const {
        return m_quantity;
    }

    // Get the name of the station (same as the item name)
    const string& Station::getName() const {
        return m_itemName;
    }

    // Update the quantity of items in the station (decrement by 1)
    void Station::updateQuantity() {
        if (m_quantity > 0)
            --m_quantity;
    }

    // Display the information of the station, optionally including full details
    void Station::display(ostream& os, bool full) const {
        os << setw(3) << right << setfill('0') << m_id << " | "
            << left << setw(m_widthField) << setfill(' ') << m_itemName << " | "
            << right << setw(6) << setfill('0') << m_serialNumber << " | ";
        if (full) {
            os << setw(4) << setfill(' ') << m_quantity << " | " << m_description;
        }
        os << endl;
    }

}  // namespace sdds
