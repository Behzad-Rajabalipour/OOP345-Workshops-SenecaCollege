#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include <string>
#include "Cheese.h"  // Include Cheese.h for using the Cheese class

namespace sdds {

	class CheeseShop {
	private:
		std::string shopName;       // Name of the cheese shop
		const Cheese** inventory;   // Array of pointers to const Cheese objects
		size_t inventorySize;       // Size of the inventory

	public:
		// Constructor with a default parameter for shopName
		CheeseShop(const std::string & = "No Name");

		// Function to add a Cheese to the shop's inventory
		CheeseShop& addCheese(const Cheese&);

		// Copy constructor
		CheeseShop(const CheeseShop&);

		// Move constructor (noexcept specifier indicates it won't throw exceptions)
		CheeseShop(CheeseShop&&) noexcept;

		// Copy assignment operator
		CheeseShop& operator=(const CheeseShop&);

		// Move assignment operator (noexcept specifier indicates it won't throw exceptions)
		CheeseShop& operator=(CheeseShop&&) noexcept;

		// Destructor
		~CheeseShop();

		// Overloaded stream insertion operator as a friend function
		friend std::ostream& operator<<(std::ostream&, const CheeseShop&);
	};

}  // namespace sdds

#endif // !SDDS_CHEESESHOP_H
