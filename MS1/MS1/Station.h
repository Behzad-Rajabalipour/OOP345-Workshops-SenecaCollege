#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>
#include <iostream>

namespace sdds {
    class Station {
        int m_id;                    // Station ID
        std::string m_itemName;      // Name of the item at the station
        std::string m_description;   // Description of the station
        size_t m_serialNumber;       // Current serial number of the station
        size_t m_quantity;           // Quantity of items at the station
        static size_t m_widthField;  // Width used to display the fields
        static int id_generator;     // ID generator for unique station IDs

    public:
        // Constructor that initializes the Station object based on the record
        Station(const std::string& record);

        // Returns the name of the item at the station
        const std::string& getItemName() const;

        // Returns the next available serial number and increments it
        size_t getNextSerialNumber();

        // Returns the quantity of items at the station
        size_t getQuantity() const;

        // Updates the quantity of items at the station by subtracting one
        void updateQuantity();

        // Displays the information about the station
        void display(std::ostream&, bool) const;
    };
}

#endif // !SDDS_STATION_H
