#include "Utilities.h"
#include <stdexcept>            // Include <stdexcept> for exception handling 

using namespace std;

namespace sdds {

    // Static member initialization
    char Utilities::m_delimiter = '|';  // Default delimiter for token extraction

    // Default constructor, initializes widthField to 0
    Utilities::Utilities() : m_widthField(0) {}

    // Set the widthField to a new value
    void Utilities::setFieldWith(size_t newWidth) {
        m_widthField = newWidth;
    }

    // Get the current value of widthField
    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    // Extract a token from the given string
    string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
        size_t end_pos = str.find(m_delimiter, next_pos);
        string token;

        // If delimiter is not found, set 'more' to false and get the remaining substring
        if (end_pos == std::string::npos) {
            more = false;
            token = str.substr(next_pos);
        }
        // If the next position is the delimiter, set 'more' to false and throw an exception 
        else if (end_pos == next_pos) {
            more = false;
            throw invalid_argument("Delimiter found at next_pos");
        }
        // Extract the token between the current and next delimiter positions
        else {
            token = str.substr(next_pos, end_pos - next_pos);
            next_pos = end_pos + 1;
            more = next_pos < str.size();
        }

        // Trim leading and trailing whitespaces from the token
        size_t start = token.find_first_not_of(" ");
        token = (start == string::npos) ? token : token.substr(start);
        size_t end = token.find_last_not_of(" ");
        token = (end == string::npos) ? token : token.substr(0, end + 1);

        // Update widthField if the current token length is greater
        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }

        return token;
    }

    // Set a new delimiter
    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    // Get the current delimiter
    char Utilities::getDelimiter() {
        return m_delimiter;
    }

}  // namespace sdds
