#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Station.h"

namespace sdds {
	class CustomerOrder {
		// A private inner struct to represent an item in the customer order
		struct Item {
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			// Constructor initializes the item with a name
			Item(const std::string& name) : m_itemName(name) {};
		};

		// Private members of the CustomerOrder class
		std::string m_name;      // Customer name (e.g., Cornel B.)
		std::string m_product;   // Product information (e.g., 1-Room Home Office)
		size_t m_cntItem;        // Number of items in the order (e.g., 5)
		Item** m_items;          // Array of pointers to Item objects representing the items in the order
		static size_t m_widthField;  // Static member for formatting output

	public:
		// Public member functions of the CustomerOrder class
		CustomerOrder();  // Default constructor
		CustomerOrder(const std::string&);  // Constructor with a string parameter representing the order details

		// Copy constructor
		CustomerOrder(const CustomerOrder&);

		// Move constructor and move assignment operator with noexcept specifier
		CustomerOrder(CustomerOrder&&) noexcept;
		CustomerOrder& operator=(CustomerOrder&&) noexcept;

		// Member functions to check if the order or a specific item is filled
		bool isOrderFilled() const;
		bool isItemFilled(const std::string&) const;

		// Function to fill an item at a station and display the result
		void fillItem(Station&, std::ostream&);

		// Function to display the order details
		void display(std::ostream&) const;

		// Destructor to clean up dynamically allocated memory
		~CustomerOrder();
	};
}

#endif // SDDS_CUSTOMERORDER_H
