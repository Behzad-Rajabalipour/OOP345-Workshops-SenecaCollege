#include "Utilities.h"
#include <stdexcept> // For error handling, e.g., throw error. 

using namespace std;

namespace sdds {
    // Initialize static member outside the class definition
    char Utilities::m_delimiter = '|'; // Initialize the delimiter to '|'

    // Default constructor
    Utilities::Utilities() : m_widthField(0) {};

    // Set the width of the field
    void Utilities::setFieldWith(size_t newWidth) {
        m_widthField = newWidth;
    }

    // Get the width of the field
    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    // Extract a token from the input string
    string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
        size_t end_pos = str.find(m_delimiter, next_pos); // Find the position of the delimiter. m_delimiter is accessed from within the class. 

        // Check if the delimiter is not found at the end
        if (end_pos == std::string::npos) {
            more = false;
            string token = str.substr(next_pos);

            // Update the widthField if necessary
            if (m_widthField < token.length()) {
                m_widthField = token.length();
            }
            return token;
        }

        // Check if the delimiter is found at the current position
        if (end_pos == next_pos) {
            more = false;
            throw invalid_argument("delimiter found at next_pos"); // Throw an exception if the delimiter is found at next_pos. 
        }

        // Extract the token and update the next_pos
        string token = str.substr(next_pos, end_pos - next_pos);
        next_pos = end_pos + 1;
        more = next_pos < str.size(); // Set more to true or false based on the condition

        // Update the widthField if necessary
        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }

        return token;
    }

    // Set the delimiter
    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter; // Set the delimiter. Static member is modified within the class.
    }

    // Get the delimiter. A static member is accessed without using the class name.
    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}
