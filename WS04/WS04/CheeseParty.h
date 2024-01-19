#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include <iostream>
#include "Cheese.h"  // Include Cheese.h for using the Cheese class

namespace sdds {

	class CheeseParty {
		const Cheese** cheeses;   // Array of pointers to const Cheese objects
		size_t cheeseCount;       // Number of cheeses in the party

	public:
		// Default constructor
		CheeseParty();

		// Function to add a Cheese to the party
		CheeseParty& addCheese(const Cheese&);

		// Function to remove a Cheese from the party
		CheeseParty& removeCheese();

		// Copy constructor
		CheeseParty(const CheeseParty&);

		// Move constructor (noexcept specifier indicates it won't throw exceptions)
		CheeseParty(CheeseParty&&) noexcept;

		// Copy assignment operator
		CheeseParty& operator=(const CheeseParty&);

		// Move assignment operator (noexcept specifier indicates it won't throw exceptions)
		CheeseParty& operator=(CheeseParty&&) noexcept;

		// Destructor
		~CheeseParty();

		// Overloaded stream insertion operator as a friend function
		friend std::ostream& operator<<(std::ostream&, const CheeseParty&);
	};

} // namespace sdds

#endif // !SDDS_CHEESEPARTY_H
