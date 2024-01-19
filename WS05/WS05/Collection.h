#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include <string>

// Avoid using "using namespace std" in header files to prevent naming conflicts.

namespace sdds {
    template<typename T>
    class Collection {
        std::string m_name = "";
        T* m_items{ nullptr }; // Array of type T
        size_t m_size = 0;
        void (*m_observer)(const Collection<T>&, const T&) = nullptr;

        // Function to resize the array
        void resize() {
            T* newItems = new T[m_size + 1]; // Dynamic array
            for (size_t i = 0; i < m_size; i++) {
                newItems[i] = m_items[i];
            }
            delete[] m_items;
            m_items = newItems;
        }

    public:
        Collection() = default;
        Collection(const std::string& name) : m_name(name) {};
        ~Collection() { delete[] m_items; }

        const std::string& name() const { return m_name; }
        size_t size() const { return m_size; }

        // Set the observer function
        void setObserver(void (*observer)(const Collection<T>&, const T&)) {
            m_observer = observer;
        }

        // Overloaded operator+= to add an item to the collection
        Collection<T>& operator+=(const T& item) {
            for (size_t i = 0; i < m_size; i++) {
                if (m_items[i] == item)
                    return *this;
            }

            resize();
            m_items[m_size++] = item;

            // Call the observer function if set
            if (m_observer)
                m_observer(*this, item);

            return *this;
        }

        // Overloaded operator[] to access an item by index
        T& operator[](size_t index) const {
            if (index < m_size) {
                return m_items[index];
            }
            throw std::out_of_range("Bad index [" + std::to_string(index) + "]. Collection has [" + std::to_string(m_size) + "] items.");
        }

        // Overloaded operator[] to access an item by title
        T* operator[](const std::string& title) const {
            for (size_t i = 0; i < m_size; i++) {
                if (m_items[i].title() == title)
                    return &m_items[i];
            }
            return nullptr;
        }

        // Friend function to overload the stream insertion operator for Collection objects
        friend std::ostream& operator<<(std::ostream& ostr, const Collection<T>& obj) {
            for (size_t i = 0; i < obj.m_size; i++) {
                ostr << obj.m_items[i] << std::endl;
            }
            return ostr;
        }
    };
}

#endif // !SDDS_COLLECTION_H
