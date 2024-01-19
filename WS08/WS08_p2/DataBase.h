#ifndef SDDS_DATABASE_H
#define SDDS_DATABASE_H
// Workshop 8 - Smart Pointers

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
    template <typename T>
    class DataBase {
        std::vector<T> database; // A vector to store objects of type T (e.g., Profile)
    public:
        // Default constructor
        DataBase() { }

        // Constructor that takes a filename to read data from
        DataBase(const char* fn) {
            std::ifstream file(fn);
            if (!file)
                throw std::string("*** Failed to open file ") + std::string(fn) + std::string(" ***");

            // Read data from the file and populate the vector
            while (file) {
                T e; // Create an object of type T (e.g., Profile)
                try {
                    // Attempt to load data from the file into the object
                    if (e.load(file))
                        database.push_back(T(e)); // Copy the object to the vector using the copy constructor
                }
                catch (...) {
                    // Break the loop if an exception occurs during loading
                    break;
                }
            }
        }

        // Return the size of the vector
        size_t size() const { return database.size(); }

        // Overloaded subscript operator for read-only access to elements
        const T& operator[](size_t i) const { return database[i]; }

        // Overloaded operator+= for adding objects by raw pointer
        DataBase& operator+=(T& profile) {
            // Add the object to the vector
            this->database.push_back(profile);
            return *this;
        }

        // Overloaded operator+= for adding objects by shared pointer
        DataBase& operator+=(std::shared_ptr<T> profile) {
            // Dereference the shared pointer and add the object to the vector
            database.push_back(*profile);
            return *this;
        }

        // Iterator type for the class
        using iterator = typename std::vector<T>::iterator;

        // Begin iterator for non-const objects
        iterator begin() { return database.begin(); }

        // End iterator for non-const objects
        iterator end() { return database.end(); }

        // Const iterator type for the class
        using const_iterator = typename std::vector<T>::const_iterator;

        // Begin iterator for const objects
        const_iterator begin() const { return database.cbegin(); }

        // End iterator for const objects
        const_iterator end() const { return database.cend(); }

        // Display function to output data to the provided ostream
        void display(std::ostream& os) const {
            os << std::fixed << std::setprecision(2);
            for (auto& e : database)
                os << e;
        }
    };

    // Overloaded output operator to display the content of the database
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const DataBase<T>& db) {
        db.display(os);
        return os;
    }
}
#endif
