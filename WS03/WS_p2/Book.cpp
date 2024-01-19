// Implementation of the Book class

#include <iostream>
#include <string>
#include "Book.h"
#include "iomanip"

using namespace std;

namespace sdds {

    // Constructor with parameters to initialize Book object
    Book::Book(const std::string& title, unsigned nChapters, unsigned nPages) : m_title(title), m_numChapters(nChapters), m_numPages(nPages) {};

    // Function to check if the Book object is valid (non-empty title)
    bool Book::isValid() const {
        return !m_title.empty();
    }

    // Copy assignment operator for Book class
    Book& Book::operator=(const Book& obj) {
        if (this != &obj) {
            // Copy values from the right-hand side object to the left-hand side object
            m_title = obj.m_title;
            m_numChapters = obj.m_numChapters;
            m_numPages = obj.m_numPages;
        }
        return *this;
    }

    // Conversion operator to double (calculating pages per chapter ratio)
    Book::operator double() const {
        return double(m_numPages) / m_numChapters;
    }

    // Print function to display Book information
    ostream& Book::print(ostream& os) const {
        if (isValid()) {
            os << right << setfill(' ') << setw(56)
                << m_title + "," + to_string(m_numChapters) + "," + to_string(m_numPages)
                << " | "
                << left << setw(15)
                << "(" + to_string(static_cast<double>(m_numPages) / m_numChapters) + ")";
        }
        else {
            cout << "| Invalid book data";
        }
        return os;
    }

    // Overloaded << operator as a friend function for easy output stream printing
    ostream& operator<<(ostream& ostr, const Book& obj) {
        obj.print(ostr);
        return ostr;
    }

}  // namespace sdds
