#include "Directory.h"
#include <algorithm>
#include <stdexcept>

namespace sdds {
    // Constructor for the Directory class.
    Directory::Directory(const std::string& name) {
        // Ensure the directory name is not empty.
        if (!name.empty()) {
            m_name = name;  // Set the name of the directory.

            // Ensure the name ends with a forward slash.
            if (m_name[m_name.size() - 1] != '/')
                m_name = m_name + '/';
        }
        else {
            m_name = '/';
        }
    }

    // Destructor for the Directory class.
    Directory::~Directory() {
        // Release memory for each resource in the directory.
        for (size_t i = 0; i < m_contents.size(); i++) {
            delete m_contents[i];
        }
    }

    // Update the parent path for the directory and its contents.
    void Directory::update_parent_path(const std::string& path) {
        m_parentPath = path;

        // Update the parent path for each resource in the directory.
        for (auto& resource : m_contents) {
            resource->update_parent_path(m_parentPath + m_name);
        }
    }

    // Get the type of the directory (NodeType::DIR).
    NodeType Directory::type() const {
        return NodeType::DIR;
    }

    // Get the full path of the directory.
    std::string Directory::path() const {
        return m_parentPath + m_name;
    }

    // Get the name of the directory.
    std::string Directory::name() const {
        return m_name;
    }

    // Get the count of resources in the directory.
    int Directory::count() const {
        return static_cast<int>(m_contents.size());
    }

    // Get the total size of all resources in the directory and its subdirectories.
    size_t Directory::size() const {
        size_t totalSize = 0u;

        // Calculate the total size of all resources.
        for (const auto& resource : m_contents) {
            totalSize += resource->size();
        }
        return totalSize;
    }

    // Add a resource to the directory.
    Directory& Directory::operator+=(Resource* resource) {
        // Check if a resource with the same name already exists.
        auto it = std::find_if(m_contents.begin(), m_contents.end(), [&](const Resource* res) {
            return res->name() == resource->name();
            });

        // Throw an exception if a resource with the same name is found.
        if (it != m_contents.end()) {
            throw std::runtime_error("Resource with the same name already exists.");
        }

        // Add the resource to the directory.
        m_contents.emplace_back(resource);

        // Update the parent path for the added resource.
        resource->update_parent_path(this->path());

        return *this;
    }

    // Find a resource by name in the directory.
    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
        for (auto& resource : m_contents) {
            // Check if the current resource has the specified name.
            if (resource->name() == name) {
                return resource;
            }

            // Check if the operation is recursive and the current resource is a directory.
            if (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end() && resource->type() == NodeType::DIR) {
                // Recursively search for the resource in subdirectories.
                auto res = static_cast<Directory*>(resource)->find(name, flags);

                // If the resource is found, return it.
                if (res != nullptr) {
                    return res;
                }
            }
        }
        // Return nullptr if the resource is not found.
        return nullptr;
    }
};
