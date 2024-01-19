#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>
#include "SpellChecker.h"

// Avoid using "using namespace std" in header files to prevent naming conflicts.

namespace sdds {
    class Book {
        std::string _author = "";
        std::string _title = "";
        std::string _country = "";
        size_t _year = 0;
        double _price = 0.0;
        std::string _description = "";

    public:
        // Default constructor
        Book() = default;

        // Constructor that takes a formatted string
        Book(const std::string& strBook);

        // Queries (Getters)
        const std::string& title() const;
        const std::string& country() const;
        const size_t& year() const;
        double& price(); // This method does not have const, as it modifies the value (_price).

        // Method to fix spelling using a SpellChecker object
        void fixSpelling(SpellChecker&);

        // Overloaded equality operator for Book objects
        bool operator==(const Book&); 

        // Friend function to overload the stream insertion operator for Book objects
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
    };
}

#endif // !SDDS_BOOK_H
