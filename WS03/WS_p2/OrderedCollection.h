// Implementation of member functions for the OrderedCollection class template

#ifndef SDDS_ORDEREDCOLLECTION_H
#define SDDS_ORDEREDCOLLECTION_H

#include <iostream>
#include "Collection.h"
#include <vector>

namespace sdds {

    // OrderedCollection class template inherits from Collection with a fixed capacity of 72
    template<typename T>
    class OrderedCollection : public Collection<T, 72> {
    public:
        // Overloaded operator to add an item to the ordered collection
        OrderedCollection& operator+=(const T& item);
    };

    // Overloaded operator to add an item to the ordered collection
    template<typename T>
    OrderedCollection<T>& OrderedCollection<T>::operator+=(const T& item) {
        if (this->m_size < 72) {  // Ensure there is space in the collection
            // Update the smallest and largest items in the collection
            this->setSmallestItem(item);
            this->setLargestItem(item);

            auto it = std::begin(this->m_items);  // Iterator pointing to the beginning of the collection
            // Find the correct position to maintain order based on the double conversion of items
            while (it != std::end(this->m_items) && double(*it) < double(item)) {
                ++it;
            }

            // Insert the item at the found position
            this->m_items.insert(it, item);
            this->incrSize();
        }
        return *this;
    }
}

#endif // !SDDS_ORDEREDCOLLECTION_H
