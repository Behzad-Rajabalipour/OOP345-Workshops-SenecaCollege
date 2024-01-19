#include "AirportModels.h"

using namespace std;

namespace sdds {

	// Implementation of the Airport class

	Airport::Airport() {
		cout << "Empty Airport";  // Default constructor, prints a message when an empty Airport is created
	}

	Airport::Airport(string code_, string name_, string city_, string state_, string country_, double latitude_, double longitude_) {
		load(code_, name_, city_, state_, country_, latitude_, longitude_);  // Parameterized constructor, initializes Airport using load function
	}

	bool Airport::isValid() const {
		return (code.empty() ? 0 : 1);  // Checks if the Airport object is valid based on the code
	}

	ostream& operator<<(ostream& os, const Airport* obj) {
		// Overloaded output stream operator to display Airport information
		if (obj->isValid()) {
			os << setw(20) << setfill('.') << right << "Airport Code: " << " : "
				<< setw(30) << setfill('.') << left << obj->code << endl;
			os << setw(20) << setfill('.') << right << "Airport Name: " << " : "
				<< setw(30) << setfill('.') << left << obj->name << endl;
			os << setw(20) << setfill('.') << right << "City: " << " : "
				<< setw(30) << setfill('.') << left << obj->city << endl;
			os << setw(20) << setfill('.') << right << "State: " << " : "
				<< setw(30) << setfill('.') << left << obj->state << endl;
			os << setw(20) << setfill('.') << right << "Country: " << " : "
				<< setw(30) << setfill('.') << left << obj->country << endl;
			os << setw(20) << setfill('.') << right << "Latitude " << " : "
				<< setw(30) << setfill('.') << left << obj->latitude << endl;
			os << setw(20) << setfill('.') << right << "Longitude " << " : "
				<< setw(30) << setfill('.') << left << obj->longitude << endl;
		}
		return os;
	}

	void Airport::load(string code_, string name_, string city_, string state_, string country_, double latitude_, double longitude_) {
		// Load function to set values for Airport object
		code = code_;
		name = name_;
		city = city_;
		state = state_;
		country = country_;
		latitude = latitude_;
		longitude = longitude_;
	}

	// Implementation of the AirportLog class
	AirportLog::AirportLog(const string& filename) {
		int record_num = 0;
		string line;

		// Count the number of records in the file
		ifstream fread(filename);
		if (fread)
			// Read each line of the file to determine the number of records
			while (getline(fread, line)) record_num++;

		// Reset the file pointer to the beginning
		fread.clear();
		fread.seekg(0, ios::beg);

		if (fread) {
			int i = 0;
			while (getline(fread, line)) {
				istringstream iss(line);
				vector <string> arr_str;
				string word;

				// Parse each line of the CSV file and create Airport objects
				while (getline(iss, word, ','))
					arr_str.push_back(word);
				// Skip the header line(i = 0) of the CSV file
				if (i != 0)
					// Create Airport objects and add them to the airports_array vector
					airports_array.emplace_back(arr_str[0], arr_str[1], arr_str[2], arr_str[3], arr_str[4], stod(arr_str[5]), stod(arr_str[6]));
				i++;
			}
		}
	}

	void AirportLog::addAirport(const Airport& obj) {
		// Add an Airport object to the vector
		airports_array.push_back(obj);
	}

	AirportLog AirportLog::findAirport(string state_, string country_) {
		AirportLog airportLog;

		// Filter airports based on state and country and add to a new AirportLog object
		for (const Airport& obj : airports_array) {
			if (obj.state == state_ && obj.country == country_) {
				airportLog.addAirport(obj);
			}
		}

		return airportLog;
	}

	Airport* AirportLog::operator[](size_t index) {
		// Overloaded subscript operator to access elements in the vector
		if (index < airports_array.size()) {
			// Check if the index is within the bounds of the vector
			Airport* ptr = &airports_array[index];
			return ptr;	// Return a pointer to the Airport object at the specified index
		}
		else {
			Airport* ptr = new Airport();  // Create a new Airport object if the index is out of bounds
			return ptr;	// Return a pointer to the newly created Airport object
		}
	}

	AirportLog::operator size_t() {
		// Conversion operator to return the size of the vector
		return airports_array.size();
	}

	AirportLog::~AirportLog() {
		// Destructor
		// Note: No specific cleanup is required as the vector manages memory for Airport objects
	}
}
