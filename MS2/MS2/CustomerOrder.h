#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Station.h"

namespace sdds {
    class CustomerOrder {
        // We use a struct inside CustomerOrder to represent items.
        // This struct can be considered as a private member of the class.
        struct Item {
            std::string m_itemName;
            size_t m_serialNumber{ 0 };
            bool m_isFilled{ false }; // Indicates whether the item is filled or not

            // Constructor for Item
            Item(const std::string& name) : m_itemName(name) {};
        };

        // Member variables
        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item** m_items; // Array of Item pointers
        static size_t m_widthField; // Shared among all instances of CustomerOrder

    public:
        // Constructors and assignment operators
        CustomerOrder();
        CustomerOrder(const std::string&);

        // Copy constructor and copy assignment operator
        CustomerOrder(const CustomerOrder&);
        // CustomerOrder& operator=(const CustomerOrder&);

        // Move constructor and move assignment operator
        CustomerOrder(CustomerOrder&&) noexcept;
        CustomerOrder& operator=(CustomerOrder&&) noexcept;

        // Member functions
        bool isOrderFilled() const;
        bool isItemFilled(const std::string&) const;
        void fillItem(Station&, std::ostream&);
        void display(std::ostream&) const;

        // Destructor
        ~CustomerOrder();
    };
}

#endif // SDDS_CUSTOMERORDER_H
