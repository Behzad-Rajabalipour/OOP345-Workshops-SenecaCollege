#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <string>

namespace sdds {

    class Book {
        std::string m_title{};          // Title of the book
        unsigned m_numChapters{};       // Number of chapters in the book (unsigned for non-negative values)
        unsigned m_numPages{};          // Total number of pages in the book
        bool isValid() const;           // Private member function to check if the book is valid

    public:
        // Default constructor (initialize members to default values)
        Book() = default;  // Alternatively: Book() {}
        
        // Parameterized constructor
        Book(const std::string&, unsigned, unsigned);

        // Copy constructor (copies values from another Book object)
        Book(const Book& obj) : m_title(obj.m_title), m_numChapters(obj.m_numChapters), m_numPages(obj.m_numPages) {};

        // Member function to print book information to an output stream
        std::ostream& print(std::ostream&) const;

        // Copy assignment operator
        Book& operator=(const Book&);

        // Conversion operator to double (for use in OrderedCollection)
        operator double() const;

        // Friend function to overload the output stream operator (<<) for Book objects
        friend std::ostream& operator<<(std::ostream&, const Book&);
    };

    // Declaration of the friend function to overload the output stream operator (<<) for Book objects
    std::ostream& operator<<(std::ostream&, const Book&);

}  // namespace sdds

#endif // !SDDS_BOOK_H
