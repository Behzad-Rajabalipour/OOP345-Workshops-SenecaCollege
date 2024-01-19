// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

    // Function to exclude profiles using raw pointers
    DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
        // Resulting database to store non-banned profiles
        DataBase<Profile> result;

        // Iterate through all profiles in the input database
        for (const auto& profile : allProfiles) {
            // Check if the profile is not banned
            if (!isBanned(profile, bannedProfiles)) {
                // Create a new profile using raw pointer and copy constructor
                Profile* newProfile = new Profile(Profile(profile.m_name, profile.m_address, profile.m_age));
                
                // Validate the address, throw an exception if invalid
                bool res = newProfile->validateAddress();
                if (!res) {
                    delete newProfile;
                    throw string("*** Invalid Address ***");
                }
                
                // Add the new profile to the result
                result += *newProfile;
                delete newProfile; // Clean up memory
            }
        }
        return result;
    }
    
    // Function to exclude profiles using smart pointers
    DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
        // Resulting database to store non-banned profiles
        DataBase<Profile> result;

        // Iterate through all profiles in the input database
        for (const auto& profile : allProfiles) {
            // Check if the profile is not banned
            if (!isBanned(profile, bannedProfiles)) {
                // Create a new profile using shared pointer and copy constructor
                shared_ptr<Profile> newProfile(new Profile(profile.m_name, profile.m_address, profile.m_age));
                
                // Validate the address, throw an exception if invalid
                bool res = newProfile->validateAddress();
                if (!res) {
                    newProfile.reset();
                    throw string("*** Invalid Address ***");
                }
                
                // Add the new profile to the result
                result += newProfile;
                newProfile.reset(); // Release ownership
            }
        }
        return result;
    }

    // Function to check if a profile is banned
    bool isBanned(const Profile& profile, const DataBase<Profile>& bannedProfiles) {
        // Iterate through all banned profiles
        for (const auto& bannedProfile : bannedProfiles) {
            // Check if the current banned profile matches the input profile
            if (profile.m_name.first_name == bannedProfile.m_name.first_name &&
                profile.m_name.last_name == bannedProfile.m_name.last_name) {
                return true; // Profile is banned
            }
        }
        return false; // Profile is not banned
    }
}
