#include "Utilities.h"
#include <stdexcept>            // Including the necessary header for throwing errors. 

using namespace std;

namespace sdds {

    // Static member initialization
    char Utilities::m_delimiter = '|';     // Initializing the static member m_delimiter with '|' as the default delimiter. 

    // Constructor initializes the Utilities object
    Utilities::Utilities() : m_widthField(0) {};

    // Set the widthField of Utilities to a new width
    void Utilities::setFieldWith(size_t newWidth) {
        m_widthField = newWidth;
    }

    // Get the current widthField of Utilities
    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    // Extract a token from the given string, updating the position and more flag
    string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
        size_t end_pos = str.find(m_delimiter, next_pos);            // Finding the position of the delimiter. m_delimiter is a static member.
        string token;

        if (end_pos == std::string::npos) {               // If the delimiter is not found at the end
            more = false;
            token = str.substr(next_pos);
        }
        else if (end_pos == next_pos) {
            more = false;
            throw invalid_argument("delimiter found at next_pos");            // Throwing an invalid_argument exception if the delimiter is found at the next_pos.
        }
        else {
            token = str.substr(next_pos, end_pos - next_pos);        // Extracting the token from the string
            next_pos = end_pos + 1;
            more = next_pos < str.size();            // Setting more to true or false based on the condition
        }

        // Trimming leading and trailing whitespaces
        size_t start = token.find_first_not_of(" ");
        token = (start == string::npos) ? token : token.substr(start);        // If start index is not found, keep the token as is. Otherwise, trim leading whitespaces.
        size_t end = token.find_last_not_of(" ");
        token = (end == string::npos) ? token : token.substr(0, end + 1);     // If end index is not found, keep the token as is. Otherwise, trim trailing whitespaces.

        // Update m_widthField if the current token length is greater
        if (m_widthField < token.length()) {      
            m_widthField = token.length();        // Updating m_widthField to the maximum length of tokens
        }

        return token;
    }

    // Set a new delimiter for Utilities
    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;                    // Setting a new delimiter for Utilities. m_delimiter is a static member.
    }

    // Get the current delimiter used by Utilities
    char Utilities::getDelimiter() {
        return m_delimiter;         // Returning the current delimiter used by Utilities. Static members can be accessed without the class qualifier.
    }
}  // namespace sdds
