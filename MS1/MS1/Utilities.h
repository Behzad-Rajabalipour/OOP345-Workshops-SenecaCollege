#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds {
    class Utilities {
        size_t m_widthField;    // The width to be used for display
        static char m_delimiter; // The delimiter used to separate fields, declared as static for shared behavior

    public:
        // Default constructor
        Utilities();

        // Sets the width of the field
        void setFieldWith(size_t);

        // Returns the width of the field
        size_t getFieldWidth() const;

        // Extracts the next token from the input string
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

        // Sets the delimiter for all Utilities objects
        static void setDelimiter(char newDelimiter);

        // Returns the delimiter for all Utilities objects
        static char getDelimiter();
    };
}

#endif // !SDDS_UTILITIES_H
