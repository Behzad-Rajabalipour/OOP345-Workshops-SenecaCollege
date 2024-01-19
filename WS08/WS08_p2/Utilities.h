// Workshop 8 - Smart Pointers

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include "DataBase.h"
#include "Profile.h"

namespace sdds {

    // Function to exclude profiles using raw pointers
    DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles);

    // Function to check if a profile is banned
    bool isBanned(const Profile& profile, const DataBase<Profile>& bannedProfiles);

    // Function to exclude profiles using smart pointers
    DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles);
}

#endif
