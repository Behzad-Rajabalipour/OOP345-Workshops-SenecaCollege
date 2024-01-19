#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

namespace sdds {
    class Station {
        // Member variables
        int m_id;               // Unique identifier for the station
        std::string m_itemName; // Name of the item the station holds
        std::string m_description; // Description of the station
        size_t m_serialNumber;  // Serial number for the next item processed
        size_t m_quantity;      // Quantity of items available at the station
        static size_t m_widthField;  // Common width field for display alignment
        static int id_generator;     // Generator for unique IDs

    public:
        // Constructor
        Station(const std::string& record);

        // Member functions
        const std::string& getItemName() const;  // Returns the name of the item
        size_t getNextSerialNumber();            // Returns the next serial number
        size_t getQuantity() const;              // Returns the quantity of items
        void updateQuantity();                   // Updates the quantity of items
        void display(std::ostream&, bool) const; // Displays station information

    };
}

#endif // !SDDS_STATION_H
