#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <vector>
#include <algorithm>   // Required for the algorithm functions like all_of
#include <stdexcept>   // Required for runtime_error
using namespace std;

namespace sdds {
    // Static member initialization
    size_t CustomerOrder::m_widthField = 0;

    // Default constructor
    CustomerOrder::CustomerOrder() : m_cntItem(0), m_items(nullptr) {}

    // Custom constructor
    CustomerOrder::CustomerOrder(const string& str) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;
        m_cntItem = 0;

        // Extract customer name and product using Utilities
        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);

        // Extract items into a vector
        vector<string> items;
        while (more) {
            items.push_back(util.extractToken(str, next_pos, more));
        }

        m_cntItem = items.size();

        // Allocate memory for items
        m_items = new Item * [m_cntItem];

        // Create Item objects for each item in the order
        for (size_t i = 0; i < m_cntItem; i++) {
            m_items[i] = new Item(items[i]);
        }

        // Update the widthField if necessary
        if (CustomerOrder::m_widthField < util.getFieldWidth()) {
            CustomerOrder::m_widthField = util.getFieldWidth();
        }
    }

    // Copy constructor (deleted)
    CustomerOrder::CustomerOrder(const CustomerOrder& other) {
        throw runtime_error("cannot make copies of CustomerOrder");
    }

    // Move constructor
    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        // Move data from the source object to the current object
        m_items = other.m_items;
        m_name = move(other.m_name);
        m_product = move(other.m_product);
        m_cntItem = other.m_cntItem;

        // Reset the source object
        other.m_items = nullptr;
        other.m_cntItem = 0;
    }

    // Move assignment operator
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        // Check for self-assignment
        if (this != &other) {
            // Deallocate existing resources
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_items[i];
            }
            delete[] m_items;

            // Move data from the source object to the current object
            m_name = move(other.m_name);
            m_product = move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_items = other.m_items;

            // Reset the source object
            other.m_cntItem = 0;
            other.m_items = nullptr;
        }
        return *this;
    }

    // Check if the order is filled
    bool CustomerOrder::isOrderFilled() const {
        // Use all_of to check if all items are filled
        return all_of(m_items, m_items + m_cntItem, [](Item* item) {
            return item->m_isFilled;
            });
    }

    // Check if a specific item is filled
    bool CustomerOrder::isItemFilled(const string& itemName) const {
        // Check if the specified item is filled
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_items[i]->m_itemName == itemName && !m_items[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    // Fill an item at a station
    void CustomerOrder::fillItem(Station& station, ostream& os) {
        // Iterate through items to find a match with the station
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_items[i]->m_itemName == station.getItemName() && !m_items[i]->m_isFilled) {
                // Check if the station has enough quantity
                if (station.getQuantity() > 0) {
                    // Update item details and station quantity
                    station.updateQuantity();
                    m_items[i]->m_isFilled = true;
                    m_items[i]->m_serialNumber = station.getNextSerialNumber();

                    // Print a message indicating the item has been filled
                    os << "Filled " << m_name << ", " << m_product << " [" << m_items[i]->m_itemName << "]" << endl;
                    break;  // Exit the loop after filling one item
                }
                else {
                    // Print a message if the station is unable to fill the item
                    os << "Unable to fill " << m_name << ", " << m_product << " [" << m_items[i]->m_itemName << "]" << endl;
                }
            }
        }
    }

    // Display the customer order details
    void CustomerOrder::display(ostream& os) const {
        os << m_name << " - " << m_product << endl;

        // Display details for each item in the order
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << setw(6) << setfill('0') << m_items[i]->m_serialNumber << "] "
                << setw(m_widthField) << left << setfill(' ') << m_items[i]->m_itemName
                << " - " << (m_items[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
        }
    }

    // Destructor
    CustomerOrder::~CustomerOrder() {
        // Deallocate memory for each Item object
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_items[i];
        }
        // Deallocate memory for the array of Item pointers
        delete[] m_items;
    }
}
