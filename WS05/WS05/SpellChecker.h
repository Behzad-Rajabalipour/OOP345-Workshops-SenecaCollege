#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H

#include <iostream>
#include <string>

namespace sdds {
    class SpellChecker {
    private:
        std::string m_badWords[6];           // Array of 6 strings to store bad words
        std::string m_goodWords[6];          // Array of 6 strings to store corresponding good words
        int m_replacementCount[6]{ 0 };      // Array of 6 integers to count replacements, initialized with zeros

    public:
        SpellChecker() = default;           // Default constructor

        // Constructor that takes a C-style string containing bad and good words
        SpellChecker(const char*);

        // Function call operator to perform spell-checking on a string
        void operator()(std::string&);

        // Method to display spell-checking statistics
        void showStatistics(std::ostream&) const;
    };
}

#endif // !SDDS_SPELLCHECKER_H
