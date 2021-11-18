#pragma once
#include <string>
#include <algorithm>
#include "name-type.h"

/**
 * Entry object for the address book, could be used in other applications
 *
 * Contains a first name, last name and optional phone number
 *
 */
class Entry {
    private:
    std::string firstName = "", lastName = "", phoneNumber = "";
    
    public:
    Entry(std::string firstName, std::string lastName, std::string phoneNumber = "")
        : firstName{firstName},
          lastName{lastName},
          phoneNumber{phoneNumber} 
        { }
    /*
    *   Getters for properties & toString method for printing the entries
    */
    const std::string getFirstName() const { return firstName; }
    const std::string getLastName() const { return lastName; }
    const std::string getPhoneNumber() const { return phoneNumber; }
    /**
    * Prints the Entry fields into the console
    *
    * @param nameOrder What order the names should be displayed in, first name first
    * or second name first
    * @return a formatted string containing the Entry properties
    */
    const std::string toString(NameType nameOrder = NameType::FIRSTNAME) const;

    // overload `<` operator to use a `Entry` object as a key in the set for first name sorting
    bool operator<(Entry const &entry) const {
        return firstName < entry.firstName || (firstName == entry.firstName && lastName < entry.lastName);
    }

    // overload `>` operator to use a `Entry` object as a key in the set for last name sorting
    bool operator>(Entry const &entry) const {
        return lastName < entry.lastName || (lastName == entry.lastName && firstName < entry.firstName);
    }
};