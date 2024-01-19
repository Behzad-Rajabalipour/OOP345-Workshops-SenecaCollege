#include <iostream>
#include "Cheese.h"
#include "CheeseParty.h"

using namespace std;

namespace sdds {

	// Default constructor
	CheeseParty::CheeseParty() : cheeses(nullptr), cheeseCount(0) {};

	// Function to add a Cheese object to the party
	CheeseParty& CheeseParty::addCheese(const Cheese& obj) {
		for (size_t i = 0; i < cheeseCount; i++) {
			if (cheeses[i] == &obj) {
				return *this;  // Cheese is already in the party
			}
		}

		// Allocate memory for a new array of pointers
		const Cheese** temp = new const Cheese * [cheeseCount + 1];

		// Copy existing pointers to the new array
		for (size_t i = 0; i < cheeseCount; i++) {
			temp[i] = cheeses[i];
		}

		temp[cheeseCount] = &obj;  // Add the new Cheese object to the array

		delete[] cheeses;  // Delete the old array

		cheeses = temp;  // Update the pointer to the new array
		cheeseCount++;

		return *this;
	}

	// Function to remove Cheese objects with weight zero from the party
	CheeseParty& CheeseParty::removeCheese() {
		// Count the number of non-zero weight Cheese objects
		size_t new_cheeseCount = 0;
		for (size_t i = 0; i < cheeseCount; i++) {
			if (cheeses[i] && cheeses[i]->weight != 0) {
				new_cheeseCount++;
			}
		}

		// If no removal needed, return current object
		if (new_cheeseCount == cheeseCount) {
			return *this;
		}

		// Create a new array to store non-zero weight Cheese objects
		const Cheese** temp = new const Cheese * [new_cheeseCount];

		// Copy non-zero weight Cheese objects to the new array
		size_t j = 0;
		for (size_t i = 0; i < cheeseCount; i++) {
			if (cheeses[i] && cheeses[i]->weight != 0) {
				temp[j] = cheeses[i];
				j++;
			}
		}

		delete[] cheeses;  // Delete the old array
		cheeses = temp;    // Update the pointer to the new array
		cheeseCount = new_cheeseCount;

		return *this;
	}

	// Destructor
	CheeseParty::~CheeseParty() {
		delete[] cheeses;  // Delete the array of pointers
	}

	// Copy constructor
	CheeseParty::CheeseParty(const CheeseParty& obj) : cheeseCount(obj.cheeseCount) {
		// Allocate memory for a new array of pointers
		cheeses = new const Cheese * [cheeseCount];

		// Copy each pointer from the source object to the new array
		for (size_t i = 0; i < cheeseCount; i++) {
			cheeses[i] = obj.cheeses[i];
		}
	}

	// Move constructor
	CheeseParty::CheeseParty(CheeseParty&& obj) noexcept : cheeseCount(obj.cheeseCount) {
		// Move ownership of the array of pointers from the source object to the current object
		cheeses = obj.cheeses;

		// Set the source object's pointer to null and update its cheese count
		obj.cheeses = nullptr;
		obj.cheeseCount = 0;
	}

	// Copy assignment operator
	CheeseParty& CheeseParty::operator=(const CheeseParty& obj) {
		if (this != &obj) {
			// Delete the existing array of pointers
			delete[] cheeses;

			// Copy the cheese count
			cheeseCount = obj.cheeseCount;

			// Allocate memory for a new array of pointers
			cheeses = new const Cheese * [cheeseCount];

			// Copy each pointer from the source object to the new array
			for (size_t i = 0; i < cheeseCount; i++) {
				cheeses[i] = obj.cheeses[i];
			}
		}
		return *this;
	}

	// Move assignment operator
	CheeseParty& CheeseParty::operator=(CheeseParty&& obj) noexcept {
		if (this != &obj) {
			// Delete the existing array of pointers
			delete[] cheeses;

			// Move ownership of the array of pointers from the source object to the current object
			cheeses = obj.cheeses;

			// Set the source object's pointer to null and update its cheese count
			obj.cheeses = nullptr;
			obj.cheeseCount = 0;
		}
		return *this;
	}

	// Overloaded stream insertion operator
	ostream& operator<<(ostream& ostr, const CheeseParty& obj) {
		ostr << "--------------------------\n";
		ostr << "Cheese Party\n";
		ostr << "--------------------------\n";

		// Check if the party is empty
		if (obj.cheeseCount == 0) {
			ostr << "This party is just getting started!\n";
		}
		else {
			// Print each Cheese object in the party
			for (size_t i = 0; i < obj.cheeseCount; i++) {
				if (obj.cheeses[i] != nullptr) {
					ostr << *obj.cheeses[i];
				}
			}
		}

		ostr << "--------------------------\n";
		return ostr;
	}
}  // namespace sdds
