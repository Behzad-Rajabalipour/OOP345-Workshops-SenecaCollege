#include <iostream>
#include <iomanip>
#include <string>
#include "AirportModels.h"

// Header guard check, will produce an error if not following the convention
#ifndef SDDS_AIRPORTMODELS_H
    #error "The header guard for 'AirportModels.h' doesn't follow the convention!"
#endif

int cout = 0;  // Global variable named 'cout', which could lead to conflicts

// Function to print a divider line with a specified count of asterisks
void printDivider(size_t cnt) {
    for (auto i = 0u; i < cnt; ++i)
        std::cout << "*";
    std::cout << std::endl;
}

// Function to print a header with a specified title
void printHeader(const char* head) {
    std::cout << std::endl;
    printDivider(53);
    std::cout << head << std::endl;
    printDivider(53);
}

int main()
{
    // Test cases for different scenarios

    // Test Case 1: Empty Airport Log entries
    printHeader("Empty Airport Log entries");

    sdds::AirportLog alog1;

    std::cout << alog1[0] << std::endl;
    std::cout << alog1[30] << std::endl;
    std::cout << alog1[50] << std::endl;
    std::cout << alog1[size_t(alog1) - 1] << std::endl;

    // Test Case 2: Non-Empty Airport Log entries
    printHeader("Non Empty Airport Log entries");

    sdds::AirportLog alog2("airport_data.csv");

    std::cout << alog2[0] << std::endl;
    std::cout << alog2[30] << std::endl;
    std::cout << alog2[100] << std::endl;
    std::cout << alog2[200] << std::endl;
    std::cout << alog2[300] << std::endl;

    std::cout << alog2[size_t(alog2) - 1] << std::endl;

    // Test Case 3: Add to Empty Airport Log
    printHeader("Add to Empty Airport Log");
    sdds::Airport a1{ "ADK","Adak Airport","Adak","AK","USA",51.87796,-176.64603 };
    sdds::Airport a2{ "DIK","Dickinson Theodore Roosevelt Regional Airport","Dickinson","ND","USA",46.79739,-102.80195 };
    sdds::Airport a3{ "IMT","Ford Airport","Iron Mountain/Kingsford","MI","USA",45.81835,-88.11454 };
    sdds::Airport a4{ "TYS","McGhee Tyson Airport","Knoxville","TN","USA",35.81249,-83.99286 };
    alog1.addAirport(a1);
    alog1.addAirport(a2);
    alog1.addAirport(a3);
    alog1.addAirport(a4);

    std::cout << alog1[0] << std::endl;
    std::cout << alog1[1] << std::endl;
    std::cout << alog1[2] << std::endl;
    std::cout << alog1[size_t(alog1) - 1] << std::endl;

    // Test Case 4: Find specific state's airports
    printHeader("Find specific state's airports");
    sdds::AirportLog found = alog2.findAirport("AK", "USA");
    std::cout << "Number of matches found: " << size_t(found) << std::endl;
    std::cout << "First match found:\n" << found[0] << std::endl;
    std::cout << "Last match found:\n" << found[size_t(found) - 1] << std::endl;

    // Test Case 5: Find a non-existing airport
    printHeader("Find a non-existing airport");
    sdds::AirportLog notfound = alog2.findAirport("Ontario", "Canada");
    std::cout << "Number of airports found: " << size_t(notfound) << std::endl;

    return cout;  // Return value of the global variable 'cout'
}
