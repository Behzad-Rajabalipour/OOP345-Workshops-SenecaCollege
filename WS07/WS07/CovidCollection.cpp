#include <iostream>
#include <string>
#include <vector>
#include <fstream>		// for file input/output (getline()).
#include <iomanip>		// for std::setw().
#include <sstream>		// for istringstream. 
#include <algorithm>	// for std::for_each(). 
#include <numeric>		// for std::accumulate(). 
#include "CovidCollection.h"

using namespace std;

namespace sdds {
	// Constructor with file name parameter
	CovidCollection::CovidCollection(const string& filename) {
		loadFromFile(filename);
	}

	// Private member function to load data from a file
	void CovidCollection::loadFromFile(const string& filename) {
		ifstream file(filename);
		if (!file) {
			throw runtime_error("File not found");
		}

		string line;
		while (getline(file, line)) {	// #ref2
			Covid covid;
			istringstream iss(line);	// istringstream, specifically for strings

			// Reading data from the line into the Covid structure
			string temp(25, '\0');
			iss.read(&temp[0], 25);
			covid.country = temp;

			temp.clear();
			temp.resize(25, '\0');
			iss.read(&temp[0], 25);
			covid.city = temp;

			iss >> setw(25) >> covid.variant;
			iss >> setw(5) >> covid.year;
			iss >> setw(5) >> covid.cases;
			iss >> setw(5) >> covid.deaths;

			// Trimming whitespaces from the country, city, and variant fields
			covid.country = covid.country.substr(covid.country.find_first_not_of(' '));
			covid.country = covid.country.substr(0, covid.country.find_last_not_of(' ') + 1);
			covid.city = covid.city.substr(covid.city.find_first_not_of(' '));
			covid.city = covid.city.substr(0, covid.city.find_last_not_of(' ') + 1);
			covid.variant = covid.variant.substr(covid.variant.find_first_not_of(' '));

			// Adding the Covid object to the collection
			collection.push_back(covid);
		}
	}

	// Display function to show Covid data, with a default value for country
	void CovidCollection::display(ostream& out, const string& country) const {
		// Using accumulate to sum up total cases and deaths
		unsigned int totalCases = accumulate(collection.begin(), collection.end(), 0u, [](unsigned int sum, const Covid& covid) {
			return sum + covid.cases;
			});

		unsigned int totalDeath = accumulate(collection.begin(), collection.end(), 0u, [](unsigned int sum, const Covid& covid) {
			return sum + covid.deaths;
			});

		unsigned int countrycases = 0;
		unsigned int countryDeaths = 0;
		if (country != "ALL") {
			// Calculating total cases and deaths for a specific country
			for (const Covid& item : collection) {
				if (item.country == country) {
					countrycases += item.cases;
					countryDeaths += item.deaths;
				}
			}
		}

		// Displaying information based on country
		country != "ALL" && out << "Displaying information of country = " << country << endl;

		// Using for_each to iterate through the collection and display data
		for_each(collection.begin(), collection.end(), [&out, &country](const Covid& covid) {	
			if (country == "ALL") {
				out << covid << endl;
			}
			else if (covid.country == country) {
				out << covid << endl;
			}
			});

		// Displaying additional information for a specific country
		if (country != "ALL") {
			out << "----------------------------------------------------------------------------------------" << endl
				<< "| " << right << setw(80) << "Total cases in " + country + ": " << setw(4) << countrycases << " |" << endl
				<< "| " << setw(84) << "Total deaths in " + country + ": " + to_string(countryDeaths) << " |" << endl
				<< "| " << setw(86) << country + " has " + to_string((double)countrycases / totalCases * 100)
				+ "% of global cases and " + to_string((double)countryDeaths / totalDeath * 100) + "% of global deaths |" << endl;
		}
		else {
			// Displaying total cases and deaths worldwide
			out << "| " << setw(79) << "Total cases around the world: " << totalCases << " |" << endl
				<< "| " << setw(79) << "Total deaths around the world: " << totalDeath << " |" << endl;
		}
	}

	// Overloaded operator+= to add a Covid record to the collection
	CovidCollection& CovidCollection::operator+=(Covid obj) {
		collection.push_back(obj);
		return *this;
	}

	// Sorting the collection based on a specified field
	void CovidCollection::sort(const string& field) {
		// Using std::sort to sort the collection based on the specified field
		std::sort(collection.begin(), collection.end(), [&](const Covid& a, const Covid& b) {
			if (field == "country") {
				return a.country == b.country ? a.deaths < b.deaths : a.country < b.country; // Ascending order if country is the same
			}
			else if (field == "city") {
				return a.city == b.city ? a.deaths > b.deaths : a.city < b.city; // Descending order if city is the same
			}
			else if (field == "variant") {
				return a.variant == b.variant ? a.deaths < b.deaths : a.variant < b.variant;
			}
			else if (field == "year") {
				return a.year == b.year ? a.deaths < b.deaths : a.year < b.year;
			}
			else if (field == "cases") {
				return a.cases == b.cases ? a.deaths > b.deaths : a.cases < b.cases;
			}
			else if (field == "deaths") {
				return a.deaths < b.deaths;
			}
		// Default sorting by country
		return a.country < b.country;
			});
	}

	// Checking if a particular Covid record is in the collection
	bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const {
		// Using any_of to check if any record matches the specified conditions
		return any_of(collection.begin(), collection.end(), [&](const Covid& item) {	
			return item.variant == variant && item.country == country && item.deaths > deaths;
			});
	}

	// Getting a vector of Covid records for a specified number of deaths
	vector<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const {
		vector<Covid> resultVector;

		// Using copy_if to copy records that meet the specified condition
		copy_if(collection.begin(), collection.end(), back_inserter(resultVector), [&deaths](const Covid& item) {
			return item.deaths >= deaths;	
			});

		return resultVector;
	}

	// Updating severity status based on certain conditions
	void CovidCollection::updateStatus() {
		for (Covid& item : collection) {
			if (item.deaths > 300)
				item.severityStatus = "EPIDEMIC";
			else if (item.deaths < 50)
				item.severityStatus = "EARLY";
			else
				item.severityStatus = "MILD";
		}
	}

	// Overloaded operator<< to output a Covid record
	ostream& operator<<(ostream& out, const Covid& theCovid) {
		out << "| " << left << std::setw(22) << theCovid.country
			<< "| " << setw(16) << theCovid.city
			<< "| " << setw(21) << theCovid.variant
			<< "| " << right << std::setw(6) << (theCovid.year >= 0 ? std::to_string(theCovid.year) : "") << " "
			<< "| " << setw(4) << theCovid.cases << " "
			<< "| " << setw(3) << theCovid.deaths << " | "
			<< "| " << setw(8) << theCovid.severityStatus << " |";

		return out;
	}

	// Overloaded operator<< to output the entire CovidCollection
	ostream& operator<<(ostream& out, const CovidCollection& obj) {
		for (const Covid& covid : obj) {	// Using iterator to iterate through the collection. 
			out << covid << endl;
		}
		return out;
	}
}
