#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <deque>            // deque is used for dynamic collections
#include <string>
#include "Station.h"
#include "CustomerOrder.h"

// extern keyword indicates global variables defined in other source files
extern std::deque<sdds::CustomerOrder> g_pending;       // Declared in LineManager.cpp 
extern std::deque<sdds::CustomerOrder> g_completed;     // Declared in Workstation.cpp 
extern std::deque<sdds::CustomerOrder> g_incomplete;

namespace sdds {
    // Workstation class inherits from Station
    class Workstation : public Station {
        std::deque<sdds::CustomerOrder> m_customersOrders;  // Deque to store CustomerOrders
        Workstation* m_nextWorkStation;                     // Pointer to the next Workstation in the assembly line

    public:
        // Constructor that initializes the Workstation with the given Station name
        Workstation(const std::string& Station);

        // Member function to fill the current CustomerOrder
        void fill(std::ostream&);

        // Member function to attempt to move the current CustomerOrder to the next Workstation
        bool attemptToMoverOrder();

        // Member function to set the next Workstation in the assembly line
        void setNextStation(Workstation* station = nullptr);

        // Member function to get the next Workstation in the assembly line
        Workstation* getNextStation() const;

        // Member function to display information about the Workstation
        void display(std::ostream&) const;

        // Overloaded operator to add a CustomerOrder to the Workstation
        Workstation& operator+=(CustomerOrder&&);  // Move semantics using &&

        // Deleted copy and move constructors and assignments
        Workstation(const Workstation&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;
    };
}

#endif // !SDDS_WORKSTATION_H
