#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <vector>
#include <string>
#include <iostream> // Include necessary header for std::ostream

namespace sdds {
	// Struct to represent Covid data
	struct Covid {
		std::string country = "";
		std::string city = "";
		std::string variant = "";
		int year = 0;
		unsigned int cases = 0;
		unsigned int deaths = 0;
		std::string severityStatus = "General";
	};

	// Class representing a collection of Covid data
	class CovidCollection {
		std::vector<Covid> collection; // Vector to store Covid data

		// Private member function to load data from a file
		void loadFromFile(const std::string&);

	public:
		// Default constructor
		CovidCollection() = default;

		// Constructor with file name parameter
		CovidCollection(const std::string& filename);

		// Display function to show Covid data, with a default value for country
		void display(std::ostream& out, const std::string& country = "ALL") const;

		// Sort function to sort the collection based on a given field
		void sort(const std::string & = "country");

		// Check if a particular Covid record is in the collection
		bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;

		// Get a vector of Covid records for a specified number of deaths
		std::vector<Covid> getListForDeaths(unsigned int deaths) const;

		// Update severity status based on certain conditions
		void updateStatus();

		// Overloaded operator+= to add a Covid record to the collection
		CovidCollection& operator+=(Covid);

		// Const iterators for the class
		std::vector<Covid>::const_iterator begin() const { return collection.begin(); } 
		std::vector<Covid>::const_iterator end() const { return collection.end(); }

		// Non-const iterators for the class
		std::vector<Covid>::iterator begin() { return collection.begin(); }
		std::vector<Covid>::iterator end() { return collection.end(); }
	};

	// Overloaded operator<< to output a Covid record
	std::ostream& operator<<(std::ostream&, const Covid&);

	// Overloaded operator<< to output the entire CovidCollection
	std::ostream& operator<<(std::ostream&, const CovidCollection&);
}

#endif // !SDDS_COVIDCOLLECTION_H
