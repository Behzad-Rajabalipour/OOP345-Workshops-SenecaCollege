#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds {
    class Utilities {
        // Member variables
        size_t m_widthField;        // Common width field for display alignment
        static char m_delimiter;    // Delimiter used for token extraction (static shared among all instances)

    public:
        // Constructor
        Utilities();

        // Member functions
        void setFieldWith(size_t);       // Sets the width field
        size_t getFieldWidth() const;    // Gets the width field
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);   // Extracts a token from a string
        static void setDelimiter(char newDelimiter);    // Sets the delimiter (static, shared among all instances)
        static char getDelimiter();                       // Gets the delimiter (static)
    };
}

#endif // !SDDS_UTILITIES_H
