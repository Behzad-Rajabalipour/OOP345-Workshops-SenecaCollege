#include <iostream>
#include <string>
#include <iomanip>
#include "Cheese.h"

using namespace std;

namespace sdds {

	// Function to remove leading and trailing whitespaces from a string
	void Cheese::trim(string& str) {
		str.erase(0, str.find_first_not_of(' '));        // Erase leading whitespaces
		str.erase(str.find_last_not_of(' ') + 1);        // Erase trailing whitespaces
	}

	// Constructor that initializes Cheese object from a string
	Cheese::Cheese(const std::string& str) {
		size_t start_index = 0, found_index;

		// Extract name from the string
		found_index = str.find(',', start_index);
		name = str.substr(start_index, found_index - start_index);
		trim(name);
		start_index = found_index + 1;

		// Extract weight from the string
		found_index = str.find(',', start_index);
		weight = stoul(str.substr(start_index, found_index - start_index));
		start_index = found_index + 1;

		// Extract price from the string
		found_index = str.find(',', start_index);
		price = stod(str.substr(start_index, found_index - start_index));
		start_index = found_index + 1;

		// Extract features from the string
		while ((found_index = str.find(',', start_index)) != string::npos) {
			string feature = str.substr(start_index, found_index - start_index);
			trim(feature);
			if (!feature.empty()) {
				features += " ";
			}
			features += feature;
			start_index = found_index + 1;
		}

		// Extract the last feature in the string
		if (start_index < str.size()) {
			string lastFeature = str.substr(start_index);
			trim(lastFeature);

			if (!lastFeature.empty()) {
				features += " ";
			}
			features += lastFeature;
		}
	}

	// Function to slice a Cheese object based on weight_to_slice
	Cheese Cheese::slice(size_t weight_to_slice) {
		if (weight_to_slice <= weight) {
			Cheese sliced = *this;
			sliced.weight = weight_to_slice;
			weight -= weight_to_slice;
			return sliced;
		}
		return Cheese();  // Return a new Cheese object if weight_to_slice is greater than current weight
	}

	// Overloaded stream insertion operator as a friend function
	ostream& operator<<(ostream& ostr, const Cheese& obj) {
		// Print Cheese object details in a formatted way
		ostr << "|" << std::left << std::setw(21) << obj.name
			<< "|" << std::setw(5) << obj.weight
			<< "|" << std::fixed << std::setprecision(2) << std::setw(5) << obj.price
			<< "| " << std::right << std::setw(32) << obj.features
			<< " |" << std::endl;
		return ostr;
	}

}  // namespace sdds
