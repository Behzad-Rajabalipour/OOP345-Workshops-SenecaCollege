#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <string>
#include <vector>
#include "Resource.h"
#include "Flags.h"

namespace sdds {
    class Directory : public Resource {
        std::string m_name;                     // Name of the directory
        std::string m_parentPath;               // Parent path of the directory
        std::vector<Resource*> m_contents;      // Vector storing pointers to child resources (derived from Resource)
    public:
        Directory(const std::string& name);
        virtual ~Directory();

        // Overrides from the base class Resource
        void update_parent_path(const std::string& path) override;  // Override method to update the parent path
        NodeType type() const override;          // Override method to return the node type
        std::string path() const override;       // Override method to return the full path
        std::string name() const override;       // Override method to return the name
        int count() const override;               // Override method to return the count of resources
        size_t size() const override;             // Override method to return the total size of resources

        // Operator to add a resource to the directory
        Directory& operator+=(Resource* resource);

        // Method to find a resource by name, with optional flags
        Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {});

        // Disable copy constructor and copy assignment operator
        Directory(const Directory&) = delete;
        Directory& operator=(const Directory&) = delete;

        // Disable move constructor and move assignment operator
        Directory(Directory&&) = delete;
        Directory& operator=(Directory&&) = delete;
    };
}

#endif // !SDDS_DIRECTORY_H
