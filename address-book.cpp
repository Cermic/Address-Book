#include <iostream>
#include <algorithm>

#include "address-book.h"
#include "entry.h"
#include "utility.h"

/**
 * Adding the address is quite fast (O(log n)) and the entries remain sorted based on < operator initially
 * The idea behind this is that we save a lot of time sorting the dataset over other structures
 * where we would have to constantly maintain the sort
 */
void AddressBook::addAddress(std::string firstName, std::string lastName, std::string phoneNumber) {
    this->entries.insert(Entry(firstName, lastName, phoneNumber));
    std::cout << "Entry " << firstName << " " << lastName << " added." << std::endl;
}

/**
 * We again benefit from the existing structure for removal, the speed of removal is again
 * (O(log n)) which is quite fast
 */
void AddressBook::removeAddress(std::string firstName, std::string lastName, std::string phoneNumber) {
    const Entry entryToRemove = Entry(firstName, lastName, phoneNumber);
    const bool entryFound = this->entries.find(entryToRemove) != entries.end();
    if (!entryFound) {
        std::cout << "Entry " << firstName << " " << lastName << " specified was not found, please retry command." << std::endl;
        return;
    }
    std::cout << "Entry " << firstName << " " << lastName << " successfully removed." << std::endl;
    this->entries.erase(entryToRemove);
}

/**
 * The lookup for the entry should be (O(log n)) when dealing with < operator as the default,
 * the intention behind this is that when this type of lookup is done, there is generally a 
 * preference for last or first name. So we can set which is the more common lookup to our default
 * and when we have to use our non default (since < and > operators can't be swapped out at runtime
 * to my knowledge) we pass the data into another multiset that is instantiated using the non
 * default operator. In this case we use < as the default for first names and > for the non default
 * with last names. In the non default case the lookup would be O(N)
 * 
 * An alternative to this if space wasn't an issue would be to maintain both sets, one sorted by
 * first name (< operator) and one sorted by last name (> operator) and then we could have 
 * consistent (O(log n)) lookups
 */
void AddressBook::retrieveEntries(NameType sortBy) const {
    if (this->entries.empty()) {
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "No entries in address book..." << std::endl;
        return;
    }
    if (sortBy == NameType::FIRSTNAME) {
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Retriving entries sorted by first name..." << std::endl;
        for (Entry entry: this->entries) {
            std::cout << entry.toString() << std::endl;
        }
    }
    else {
        std::multiset<Entry, std::greater<Entry>> reversedEntries;
        for (Entry entry: this->entries) {
            reversedEntries.insert(entry);
        }
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Retriving entries sorted by last name..." << std::endl;
        for (Entry entry: reversedEntries) {
            std::cout << entry.toString(NameType::LASTNAME) << std::endl;
        }
    }
}

/**
 * This function uses the same premise as retrieveEntries, but this time uses a custom comparator
 * to allow for searches to be done on individual Entry properties using lower bound to check
 * for them all. This should also be (O(log n)) for the default (< operator) and O(N) for the
 * non default (> operator). Again though, if space wasn't a big issue the lists could be
 * maintained in parrallel.
 */
void AddressBook::findAddresses(std::string searchedName, NameType sortBy) const {
    if (this->entries.empty()) {
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "No entries in address book..." << std::endl;
        return;
    }
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Retriving entries matching " << searchedName << "..." << std::endl;
    // This may be a good way to 
    const std::string lowerCaseSearchedName = Utility::toLower(searchedName);
    if (sortBy == NameType::FIRSTNAME) {
        for (auto it = std::lower_bound(this->entries.begin(), this->entries.end(), lowerCaseSearchedName, FirstNamePropComp()); it != this->entries.end(); it++) {
            if (it->getFirstName().compare(0, lowerCaseSearchedName.size(), lowerCaseSearchedName) == 0) 
            { 
                std::cout << it->toString() << std::endl;
            }
        }
    }
    else {
        std::multiset<Entry, std::greater<Entry>> reversedEntries;
        for (Entry entry: this->entries) {
            reversedEntries.insert(entry);
        }
        for (auto it = std::lower_bound(reversedEntries.begin(), reversedEntries.end(), lowerCaseSearchedName, LastNamePropComp()); it != reversedEntries.end(); it++) {
            if (it->getLastName().compare(0, lowerCaseSearchedName.size(), lowerCaseSearchedName) == 0) 
            { 
                std::cout << it->toString(NameType::LASTNAME) << std::endl;
            }
        }
    }
}