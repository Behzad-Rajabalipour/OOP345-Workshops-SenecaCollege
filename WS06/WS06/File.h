#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <string>
#include "Resource.h"
#include "Flags.h"

namespace sdds {
    class File : public Resource {
        std::string m_name;         // Name of the file
        std::string m_contents;     // Contents of the file
        std::string m_parentPath;   // Parent path of the file

    public:
        // Constructor with optional parameters for name and content
        File(const std::string& name, const std::string& content = "");

        // Overrides from the base class Resource
        void update_parent_path(const std::string& path) override;  // Override method to update the parent path
        NodeType type() const override;          // Override method to return the node type
        std::string path() const override;       // Override method to return the full path
        std::string name() const override;       // Override method to return the name
        int count() const override;               // Override method to return the count of resources (always 1 for a file)
        size_t size() const override;             // Override method to return the size of the file content
    };
}

#endif // !SDDS_FILE_H
