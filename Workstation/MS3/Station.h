#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

namespace sdds {
	class Station {
		int m_id;                  // Station ID
		std::string m_itemName;   // Name of the item at the station
		std::string m_description; // Description of the item
		size_t m_serialNumber;     // Serial number for the next item to be processed
		size_t m_quantity;         // Quantity of items available at the station
		static size_t m_widthField; // Maximum width for display purposes
		static int id_generator;   // Generator for unique station IDs

	public:
		// Constructor: Initializes the station based on the information in the provided record
		Station(const std::string& record);

		// Member function to get the name of the item at the station
		const std::string& getItemName() const;

		// Member function to get the next serial number and update it for the next item
		size_t getNextSerialNumber();

		// Member function to get the current quantity of items available at the station
		size_t getQuantity() const;

		// Member function to get the name of the station
		const std::string& getName() const;

		// Member function to update the quantity of items (decrease by 1)
		void updateQuantity();

		// Member function to display information about the station
		void display(std::ostream&, bool) const;
	};
}

#endif // !SDDS_STATION_H
