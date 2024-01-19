#include "Book.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace sdds {
    // Constructor that takes a formatted string
    Book::Book(const string& strBook) {
        // Extracting author information
        size_t start = 0, end = strBook.find(',');
        _author = strBook.substr(start, end - start);
        _author.erase(0, _author.find_first_not_of(' '));
        _author.erase(_author.find_last_not_of(' ') + 1);

        // Extracting title information
        start = end + 1; end = strBook.find(',', start);
        _title = strBook.substr(start, end - start);
        _title.erase(0, _title.find_first_not_of(' '));
        _title.erase(_title.find_last_not_of(' ') + 1);

        // Extracting country information
        start = end + 1; end = strBook.find(",", start);
        _country = strBook.substr(start, end - start);
        _country.erase(0, _country.find_first_not_of(' '));
        _country.erase(_country.find_last_not_of(' ') + 1);

        // Extracting price information
        start = end + 1; end = strBook.find(",", start);
        _price = stod(strBook.substr(start, end - start));

        // Extracting year information
        start = end + 1; end = strBook.find(",", start);
        _year = stoi(strBook.substr(start, end - start));

        // Extracting description information
        start = end + 1; end = strBook.length();
        _description = strBook.substr(start, end - start);
        _description.erase(0, _description.find_first_not_of(' '));
        _description.erase(_description.find_last_not_of(' ') + 1);
    }

    // Queries
    const string& Book::title() const { return  _title; }
    const string& Book::country() const { return _country; }
    const size_t& Book::year() const { return _year; }
    double& Book::price() { return _price; }

    // Friend helper
    ostream& operator<<(ostream& ostr, const Book& obj) {
        ostr << right << setw(20) << obj._author << " | "
            << setw(22) << obj._title << " | "
            << setw(5) << obj._country << " | "
            << obj._year << " | "
            << setw(6) << fixed << setprecision(2) << obj._price << " | "
            << left << obj._description;
        return ostr;
    }

    // Equality operator
    bool Book::operator==(const Book& obj) {
        return (_author == obj._author && _title == obj._title && _year == obj._year);
    }

    // Function to fix spelling using a SpellChecker
    void Book::fixSpelling(SpellChecker& spellChecker) {
        spellChecker(_description);
        spellChecker(_author);
        spellChecker(_country);
    }
}
