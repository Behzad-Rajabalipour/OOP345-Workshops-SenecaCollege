#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <vector>
#include <algorithm>                    // For std::all_of

using namespace std;

namespace sdds {
    // Initialize the static member variable m_widthField
    size_t CustomerOrder::m_widthField = 0;            // Set to 0 initially, will be updated during parsing.

    // Default constructor
    CustomerOrder::CustomerOrder() : m_cntItem(0), m_items(nullptr) {};

    // Constructor that parses a string to create a CustomerOrder
    CustomerOrder::CustomerOrder(const string& str) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;
        m_cntItem = 0;

        // Extract customer name and product
        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);

        vector<string> items;
        // Extract all items and store them in the 'items' vector
        while (more) {
            items.push_back(util.extractToken(str, next_pos, more));
        }

        m_cntItem = items.size();

        m_items = new Item * [m_cntItem];          // Allocate memory for an array of Item pointers
        for (size_t i = 0; i < m_cntItem; i++) {
            m_items[i] = new Item(items[i]);       // Create an Item for each item in the vector
        }

        // Update the static widthField if needed
        if (CustomerOrder::m_widthField < util.getFieldWidth()) {
            CustomerOrder::m_widthField = util.getFieldWidth();
        }
    }

    // Copy constructor (deleted)
    CustomerOrder::CustomerOrder(const CustomerOrder& other) {
        throw runtime_error("can not make copies");
    }

    // Move constructor
    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        m_items = other.m_items;
        m_name = move(other.m_name);
        m_product = move(other.m_product);
        m_cntItem = other.m_cntItem;

        other.m_items = nullptr;
        other.m_cntItem = 0;
    }

    // Move assignment operator
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            // Delete the existing items
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_items[i];
            }
            delete[] m_items;

            // Move the data from 'other'
            m_name = move(other.m_name);
            m_product = move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_items = other.m_items;

            // Reset 'other'
            other.m_cntItem = 0;
            other.m_items = nullptr;
        }
        return *this;
    }

    // Check if all items in the order are filled
    bool CustomerOrder::isOrderFilled() const {
        return all_of(m_items, m_items + m_cntItem, [](Item* item) {
            return item->m_isFilled;
            });
    }

    // Check if a specific item in the order is filled based on the station name
    bool CustomerOrder::isItemFilled(const string& stationName) const {
        int counter = 0;
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_items[i]->m_itemName == stationName) {
                if (m_items[i]->m_isFilled) {
                    counter++;
                }
                else {
                    return false;
                }
            }
        }
        if (counter >= 0)		// Return true if at least one matching item is filled
            return true;
        return false;
    }

    // Fill an item in the order using a station
    void CustomerOrder::fillItem(Station& station, ostream& os) {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_items[i]->m_itemName == station.getItemName() && !m_items[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    // Update item and station details
                    station.updateQuantity();
                    m_items[i]->m_isFilled = true;
                    m_items[i]->m_serialNumber = station.getNextSerialNumber();

                    // Output status
                    os << setw(11) << right << "Filled " << m_name << ", " << m_product << " [" << m_items[i]->m_itemName << "]" << endl;
                    break;
                }
                else {
                    // Output unable to fill status
                    os << setw(19) << right << "Unable to fill " << m_name << ", " << m_product << " [" << m_items[i]->m_itemName << "]" << endl;
                }
            }
        }
    }

    // Display the details of the customer order
    void CustomerOrder::display(ostream& os) const {
        os << m_name << " - " << m_product << endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << setw(6) << right << setfill('0') << m_items[i]->m_serialNumber << "] "
                << setw(m_widthField) << left << setfill(' ') << m_items[i]->m_itemName
                << " - " << (m_items[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
        }
    }

    // Destructor
    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_items[i];
        }
        delete[] m_items;
    }
}
