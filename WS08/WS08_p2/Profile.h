// Workshop 8 - Smart Pointers

#ifndef SDDS_PROFILE_H
#define SDDS_PROFILE_H

#include <iomanip>
#include <string>
#include <fstream>
#include <regex> // For regular expressions #ref3

namespace sdds {

    // Length of the postal code in the Address struct
    const int Address_postal_code_length = 7;

    struct Address {
        unsigned number;
        std::string street;
        std::string postal_code;

        // Load function to read data from a file into the Address object
        bool load(std::ifstream& f) {
            f >> number >> street;

            // Reading postal code with proper length
            char postal_code_temp[1 + Address_postal_code_length + 1] = { 0 };
            f.read(postal_code_temp, Address_postal_code_length + 1);
            postal_code = std::string(postal_code_temp + 1);

            return f.good();
        }

        // Overloaded output operator for Address
        friend std::ostream& operator<<(std::ostream& os, const Address& ad) {
            os << std::setw(10) << ad.number << " "
                << std::setw(10) << ad.street << " "
                << std::setw(7) << ad.postal_code;
            return os;
        }
    };

    struct Name {
        std::string first_name;
        std::string last_name;

        // Load function to read data from a file into the Name object
        bool load(std::ifstream& f) {
            f >> first_name >> last_name;
            return f.good();
        }

        // Overloaded output operator for Name
        friend std::ostream& operator<<(std::ostream& os, const Name& n) {
            os << std::setw(10) << n.first_name << std::setw(10) << n.last_name;
            return os;
        }
    };

    struct Profile {
        static int m_idGenerator;
        int m_id{ ++m_idGenerator };
        Name m_name;
        Address m_address;
        unsigned m_age;
        static bool Trace;

        // Default constructor
        Profile() = default;

        // Load function to read data from a file into the Profile object
        bool load(std::ifstream& f) {
            m_name.load(f);
            m_address.load(f);
            f >> m_age;
            return f.good();
        }

        // Constructor with parameters
        Profile(const Name& name, const Address& addr, unsigned age) {
            this->m_name = name;
            this->m_address = addr;
            this->m_age = age;
            if (Profile::Trace)
                std::cout << "     C [" << m_id << "][" << this->m_name << "]" << std::endl;
        }

        // Copy constructor
        Profile(const Profile& other) {
            this->m_name = other.m_name;
            this->m_address = other.m_address;
            this->m_age = other.m_age;
            // We add this constructor for tracing messages
            if (Profile::Trace)
                std::cout << "    CC [" << m_id << "][" << m_name << "] copy of [" << other.m_id << "]\n";
        }

        // Destructor
        ~Profile() {
            // Displaying a message if Trace is enabled
            if (Profile::Trace)
                std::cout << "    ~D [" << m_id << "][" << this->m_name << "]" << std::endl;
        }

        // Function to validate the address
        bool validateAddress() {
            if (this->m_address.number < 0 || !isValidatePostalCode(this->m_address.postal_code)) {
                return false;
            }
            return true;
        }

        // Function to check if a postal code is valid
        bool isValidatePostalCode(const std::string& postalCode) {
            std::regex pattern("[A-Za-z]\\d[A-Za-z] \\d[A-Za-z]\\d");
            return std::regex_match(postalCode, pattern);
        }

        // Overloaded output operator for Profile
        friend std::ostream& operator<<(std::ostream& os, const Profile& p) {
            os << std::setw(5) << p.m_id
                << std::setw(10) << p.m_name
                << std::setw(10) << p.m_address
                << std::setw(5) << p.m_age;
            return os << std::endl;
        }
    };

    // Initializing the static member m_idGenerator
    inline int Profile::m_idGenerator{};
}
#endif
