#include "File.h"

namespace sdds {
    // Constructor for the File class.
    // Initializes the file with a name and optional contents.
    File::File(const std::string& name, const std::string& contents) {
        // Ensure the file name is not empty.
        if (!name.empty()) {
            m_name = name;

            // If the file name starts with a forward slash, remove it.
            if (m_name[0] == '/')
                m_name = m_name.substr(1);
        }

        // Set the contents of the file.
        m_contents = contents;
    }

    // Update the parent path for the file.
    void File::update_parent_path(const std::string& path) {
        m_parentPath = path;
    }

    // Get the type of the file (NodeType::FILE).
    NodeType File::type() const {
        return NodeType::FILE;
    }

    // Get the full path of the file.
    std::string File::path() const {
        return m_parentPath + m_name;
    }

    // Get the name of the file.
    std::string File::name() const {
        return m_name;
    }

    // Get the count of resources in the file (always -1 for files).
    int File::count() const {
        return -1;
    }

    // Get the size of the file (length of contents).
    size_t File::size() const {
        return m_contents.size();
    }
}  // namespace sdds
