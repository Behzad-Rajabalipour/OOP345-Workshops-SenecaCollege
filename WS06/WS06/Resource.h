#ifndef SDDS_EVENT_H
#define SDDS_EVENT_H

#include <iostream>
#include <string>
#include "Flags.h"

namespace sdds {
    // The Resource class serves as an abstract base class for different types of filesystem resources.
    class Resource {
    protected:
        std::string m_name{};              // Name of the resource
        std::string m_parent_path = "/";   // Parent path of the resource (default is root)

    public:
        // Pure virtual function to update the parent path of the resource.
        virtual void update_parent_path(const std::string&) = 0;

        // Pure virtual function to get the name of the resource.
        virtual std::string name() const = 0;

        // Pure virtual function to get the count of the resource.
        virtual int count() const = 0;

        // Pure virtual function to get the path of the resource.
        virtual std::string path() const = 0;

        // Pure virtual function to get the size of the resource.
        virtual size_t size() const = 0;

        // Pure virtual function to get the type of the resource (Directory or File).
        virtual NodeType type() const = 0;

        // Virtual destructor for proper polymorphic behavior.
        virtual ~Resource() {}
    };
}  // namespace sdds

#endif
