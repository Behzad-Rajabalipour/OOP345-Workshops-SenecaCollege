#ifndef SDDS_FLAGS_H
#define SDDS_FLAGS_H

namespace sdds
{
    // Options for displaying the files and directories
    enum class FormatFlags {
        LONG,     // Display in long format
    };

    // Determine the type of filesystem resource
    enum class NodeType {
        DIR,   // Directory
        FILE   // Regular File
    };

    // Options for performing a filesystem operation
    enum class OpFlags {
        RECURSIVE,  // Perform an operation recursively
    };
}
#endif
