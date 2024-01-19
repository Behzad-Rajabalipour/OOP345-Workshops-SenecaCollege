#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "iomanip"

// Declaration of the sdds namespace
namespace sdds {

    // Declaration of the Airport class
    class Airport {
        std::string code;       // Airport code
        std::string name;       // Airport name
        std::string city;       // City where the airport is located
        std::string state;      // State where the airport is located
        std::string country;    // Country where the airport is located
        double latitude;        // Latitude coordinates of the airport
        double longitude;       // Longitude coordinates of the airport

    public:
        // Constructors and member functions of the Airport class
        Airport();  // Default constructor
        Airport(std::string, std::string, std::string, std::string, std::string, double, double);  // Parameterized constructor
        void load(std::string, std::string, std::string, std::string, std::string, double, double);  // Load data into the Airport object
        bool isValid() const;   // Check if the Airport object is valid
        friend std::ostream& operator<<(std::ostream&, const Airport*);  // Overloaded output stream operator
        friend class AirportLog;  // Friend class declaration for AirportLog
    };

    // Declaration of the AirportLog class
    class AirportLog {
        std::vector <Airport> airports_array;  // Vector to store instances of Airport class

    public:
        // Constructors and member functions of the AirportLog class
        AirportLog() {};  // Default constructor
        AirportLog(const std::string&);  // Parameterized constructor with file name
        ~AirportLog();  // Destructor

        // Add an Airport object to the vector
        void addAirport(const Airport&);

        // Find and return an AirportLog object based on city and state
        AirportLog findAirport(std::string, std::string);

        // Overloaded subscript operator to access elements in the vector
        Airport* operator[](size_t);

        // Conversion operator to return the size of the vector
        operator size_t();
    };
}

#endif // SDDS_AIRPORTMODELS_H
