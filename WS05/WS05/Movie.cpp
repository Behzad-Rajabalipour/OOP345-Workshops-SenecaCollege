#include <iostream>
#include <string>
#include "Movie.h"
#include "iomanip"

using namespace std;

namespace sdds {
    // Constructor that takes a formatted string
    Movie::Movie(const string& strMovie) {
        // Extracting title information
        size_t start = 0, end = strMovie.find(',');
        title_ = strMovie.substr(start, end - start);
        title_.erase(0, title_.find_first_not_of(' '));
        title_.erase(title_.find_last_not_of(' ') + 1);

        // Extracting year information
        start = end + 1;
        end = strMovie.find(',', start);
        year = stoi(strMovie.substr(start, end - start));

        // Extracting description information
        start = end + 1;
        description = strMovie.substr(start);
        description.erase(0, description.find_first_not_of(' '));
        description.erase(description.find_last_not_of(' ') + 1);
    }

    // Getter for title
    const string& Movie::title() const {
        return title_;
    }

    // Equality operator
    bool Movie::operator==(const Movie& obj) {
        return (title_ == obj.title_ && year == obj.year && description == obj.description);
    }

    // Friend helper for output stream
    ostream& operator<<(ostream& ostr, const Movie& obj) {
        ostr << right << setw(40) << obj.title_ << " | " << obj.year << " | " << left << obj.description;
        return ostr;
    }

    // Function to fix spelling using a SpellChecker
    void  Movie::fixSpelling(SpellChecker& spellChecker) {
        spellChecker(title_);
        spellChecker(description);
    }
}
