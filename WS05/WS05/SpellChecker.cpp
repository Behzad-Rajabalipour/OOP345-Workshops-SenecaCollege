#include <iostream>
#include <string>
#include "SpellChecker.h"
#include <fstream>
#include "iomanip"

using namespace std;

namespace sdds {
    // Constructor that initializes bad and good words from a file
    SpellChecker::SpellChecker(const char* filename) {
        ifstream file(filename);
        if (!file)
            throw std::runtime_error("Bad file name!"); // Throws a runtime_error with a message if the file is not found
        // throw runtime_error("Bad file name" + string(filename)); // Alternative way to throw an error with a message

        string line;
        // Read bad and good words from the file
        for (size_t i = 0; i < 6 && getline(file, line); i++) {
            size_t index = line.find(' ');
            m_badWords[i] = line.substr(0, index);
            m_goodWords[i] = line.substr(index + 1);
            m_goodWords[i].erase(0, m_goodWords[i].find_first_not_of(' '));
        }
    }

    // Operator overload to check and correct the text based on bad and good words
    void SpellChecker::operator()(string& text) {
        // Iterate through each set of bad and good words
        for (size_t i = 0; i < 6; i++) {
            size_t index = 0;
            // Check and replace all occurrences of bad words in the text
            while ((index = text.find(m_badWords[i], index)) != string::npos) {
                text.replace(index, m_badWords[i].length(), m_goodWords[i]);
                m_replacementCount[i]++; // Increment the replacement count for the current bad word
            }
        }
    }

    // Display statistics of replacements made for each bad word
    void SpellChecker::showStatistics(ostream& os) const {
        os << "Spellchecker Statistics" << endl;
        // Display replacement statistics for each bad word
        for (size_t i = 0; i < 6; i++) {
            os << right << setw(15) << m_badWords[i] << ": " << m_replacementCount[i] << " replacements" << endl;
        }
    }
}
