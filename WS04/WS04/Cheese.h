#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>
#include <string>

namespace sdds {

	class Cheese {
		std::string name{ "NaC" };
		size_t weight{ 0 };     // size_t is a positive integer, typically 64-bit
		double price = 0;
		std::string features = "";

		// Private function to trim whitespace from a string
		void trim(std::string&);

	public:
		// Default constructor
		Cheese() = default;

		// Parameterized constructor
		Cheese(const std::string&);

		// Function to slice a cheese
		Cheese slice(size_t);

		// Overloaded stream insertion operator as a friend function
		friend std::ostream& operator<<(std::ostream&, const Cheese&);

		// Friend class declaration for CheeseParty
		friend class CheeseParty; 
	};

} // namespace sdds

#endif // !SDDS_CHEESE_H
