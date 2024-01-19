#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <iostream>
#include <vector>
#include "Workstation.h"

namespace sdds {
	class LineManager {
		std::vector<Workstation*> m_activeLine;  // Vector to store pointers to active workstations (sorted)
		size_t m_cntCustomerOrder;               // Number of customer orders in the pending state
		Workstation* m_firstWS;                  // Pointer to the first workstation in the vector

	public:
		// Constructor: Takes a filename and a vector of Workstation pointers as parameters
		LineManager(const std::string&, std::vector<Workstation*>&);

		// Function to reorder the workstations based on their next stations
		void reorderStations();

		// Function to run the assembly line and process customer orders
		bool run(std::ostream&);

		// Function to display information about the line and workstations
		void display(std::ostream&) const;
	};
}
#endif // !SDDS_LINEMANAGER_H
