#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include <vector>
#include "Book.h"
#include <iomanip>

namespace sdds {

    template <typename T, unsigned C>
    class Collection {
    protected:
        std::vector<T> m_items;     // Vector to store items, dynamic array
        unsigned m_size = 0;         // Current size of the collection
        static T m_smallestItem;     // Static member for the smallest item in the collection
        static T m_largestItem;      // Static member for the largest item in the collection
        bool isValid() const;        // Private member function to check if the collection is valid

        void setSmallestItem(const T&);  // Setter for the smallest item
        void setLargestItem(const T&);   // Setter for the largest item

    public:
        Collection() = default;         // Default constructor
        ~Collection();                  // Destructor

        unsigned size() const;          // Function to get the current size of the collection
        unsigned capacity() const;      // Function to get the capacity of the collection
        void incrSize();                // Function to increment the size of the collection

        T getSmallestItem() const;      // Function to get the smallest item in the collection
        T getLargestItem() const;       // Function to get the largest item in the collection

        bool operator+=(const T&);      // Operator to add an item to the collection
        T& operator[](unsigned);        // Operator to access an item in the collection
        void print(std::ostream& os) const;  // Function to print the collection

    };

    // Specialization for static member initialization
    template <typename T, unsigned C>
    T Collection<T, C>::m_smallestItem = T(9999);

    template <typename T, unsigned C>
    T Collection<T, C>::m_largestItem = T(-9999);

    // Specialization for Book type and size 10
    template<>
    Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

    template<>
    Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

    // Specialization for print function for Book type and size 10
    template<>
    void Collection<Book, 10>::print(std::ostream& os) const {
        if (isValid()) {
            os << "| " << "---------------------------------------------------------------------------" << "|" << std::endl;
            for (auto book : m_items) {
                os << "| " << book << " |" << std::endl;
            }
            os << "| " << "---------------------------------------------------------------------------" << "|" << std::endl;
        }
    }

    // Specialization for Book type and size 72
    template<>
    Book Collection<Book, 72>::m_smallestItem{ "",1,10000 };

    template<>
    Book Collection<Book, 72>::m_largestItem{ "",10000,1 };

    // Specialization for print function for Book type and size 72
    template<>
    void Collection<Book, 72>::print(std::ostream& os) const {
        if (isValid()) {
            os << "| " << "---------------------------------------------------------------------------" << "|" << std::endl;
            for (auto book : m_items) {
                os << "| " << book << " |" << std::endl;
            }
            os << "| " << "---------------------------------------------------------------------------" << "|" << std::endl;
        }
    }

    //----------------------
    // Implementation of member functions for the Collection class template

    // Check if the collection is valid by verifying that its size is not zero
    template<typename T, unsigned C>
    bool Collection<T, C>::isValid() const {
        return m_size != 0;
    }

    // Set the smallest item in the collection
    template<typename T, unsigned C>
    void Collection<T, C>::setSmallestItem(const T& item) {
        if (item < m_smallestItem) m_smallestItem = item;
    }

    // Set the largest item in the collection
    template<typename T, unsigned C>
    void Collection<T, C>::setLargestItem(const T& item) {
        if (item > m_largestItem) m_largestItem = item;
    }

    // Get the smallest item in the collection
    template<typename T, unsigned C>
    T Collection<T, C>::getSmallestItem() const {
        return m_smallestItem;
    }

    // Get the largest item in the collection
    template<typename T, unsigned C>
    T Collection<T, C>::getLargestItem() const {
        return m_largestItem;
    }

    // Increment the size of the collection
    template<typename T, unsigned C>
    void Collection<T, C>::incrSize() {
        m_size++;
    }

    // Get the current size of the collection
    template<typename T, unsigned C>
    unsigned Collection<T, C>::size() const {
        return m_size;
    }

    // Get the capacity of the collection
    template<typename T, unsigned C>
    unsigned Collection<T, C>::capacity() const {
        return C;
    }

    // Add an item to the collection if there is space available
    template <typename T, unsigned C>
    bool Collection<T, C>::operator+=(const T& item) {
        if (m_size < C) {
            m_items.push_back(item);
            m_size++;
            setSmallestItem(item);
            setLargestItem(item);
            return true;
        }
        return false;
    }

    // Access an item in the collection by index
    template<typename T, unsigned C>
    T& Collection<T, C>::operator[](unsigned index) {
        return m_items[index];
    }

    // Print the collection to the output stream
    template <typename T, unsigned C>
    void Collection<T, C>::print(std::ostream& os) const {
        os << '[';
        for (unsigned i = 0; i < m_size; ++i) {
            os << m_items[i] << (i != m_size - 1 ? ',' : ']');
        };
        os << '\n';
    }

    // Destructor for the Collection class
    template<typename T, unsigned C>
    Collection<T, C>::~Collection() {}


}  // namespace sdds

#endif // !SDDS_COLLECTION_H
