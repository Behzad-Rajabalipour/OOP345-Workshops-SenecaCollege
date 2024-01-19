#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

#include <iostream>
#include <string>
#include "SpellChecker.h"

namespace sdds {
    class Movie {
        std::string title_ = "";
        size_t year{ 0 };
        std::string description = "";

    public:
        Movie() = default; // Default constructor

        // Constructor that takes a formatted string
        Movie(const std::string&);

        // Getter method for the movie title
        const std::string& title() const; // The method is marked as const to indicate it doesn't modify the object

        // Method to fix spelling using a SpellChecker object
        void fixSpelling(SpellChecker&);

        // Overloaded equality operator
        bool operator==(const Movie&);

        // Friend function to overload the stream insertion operator for Movie objects
        friend std::ostream& operator<<(std::ostream&, const Movie&);
    };
}

#endif // !SDDS_MOVIE_H
