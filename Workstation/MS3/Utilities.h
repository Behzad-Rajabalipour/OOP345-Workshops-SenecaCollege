#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds {
	class Utilities {
		size_t m_widthField;    // Field width for formatting purposes
		static char m_delimiter; // Delimiter character for token extraction

	public:
		// Default constructor: Initializes widthField to 0
		Utilities();

		// Member function to set the widthField
		void setFieldWith(size_t);

		// Member function to get the current widthField
		size_t getFieldWidth() const;

		// Member function to extract a token from a string, updating the next position and more flag
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		// Static member function to set the delimiter for all Utilities objects
		static void setDelimiter(char newDelimiter); // static ensures that it affects all instances

		// Static member function to get the current delimiter
		static char getDelimiter(); // static ensures that it is common for all instances
	};
}

#endif // !SDDS_UTILITIES_H
