#include <set>
#include "entry.h"

/**
 * Created some custom comparators to allow the entries to be searched by individual property,
 * this allows for searching both first and last names and could easily be extended later
 */
struct FirstNamePropComp
{
    bool operator() (const Entry &o, const std::string &p ) const
    {
        return o.getFirstName() < p;
    }
    bool operator() (const std::string& p, const Entry& o ) const
    {
        return p < o.getFirstName();
    }
};

struct LastNamePropComp
{
    bool operator() (const Entry &o, const std::string &p ) const
    {
        return o.getLastName() < p;
    }
    bool operator() (const std::string& p, const Entry& o ) const
    {
        return p < o.getLastName();
    }
};

/**
 * Using a multiset here gives the benefit of the sorted structure of a set for lookups
 * (Red Black Tree) and means the set will keep itself sorted by a key as values are
 * pushed into it, further speeding up multiple lookups for string prefixes (partial names).
 * The multi set also allows for duplicates incase two entries have the same names or other data
 * down the line
 * 
 * Ideally, for operational speed an undordered set would be ideal, but subsequently sorting
 * the set would be very costly and defeat the purpose of using an unordered structure.
 * 
 * Similarly, a vector could be used to hold the data, but again constant sorting would be very
 * costly along with accessing the information - a map of positions stored in the vector might be
 * a less costly approach but complex to maintain. Ultimately, some testing would need to be done
 * to figure out which is faster in proper use case.
 */
class AddressBook {
    private:
    std::multiset<Entry> entries;

    public: 
    AddressBook() {}
    AddressBook(std::multiset<Entry> entries) : entries(entries) {}

    /**
    * Gets the full set of entries for reading
    */
    const std::multiset<Entry> &getEntries() const { return entries; }
    /**
    * Adds an address to the set of entries
    *
    * @param firstName First name of entry
    * @param lastName Last name of entry
    * @param phoneNumber Optional phone number of entry
    */
    void addAddress(std::string firstName, std::string lastName, std::string phoneNumber="");
    /**
    * Retrieves all entries sorted by either first name or last name
    *
    * @param sortBy Optional sorting parameter defaulted to sorting by firstname, can be changed
    * to last name or extended later to sort by more property types, this feeds into the 
    * comparators being extended too.
    */
    void retrieveEntries(NameType sortBy = NameType::FIRSTNAME) const;
    /**
    * Removes a specific address from the address book, specified by first, last name and
    * phone number if applicable
    *
    * @param firstName First name of entry
    * @param lastName Last name of entry
    * @param phoneNumber Optional phone number of entry
    */
    void removeAddress(std::string firstName, std::string lastName, std::string phoneNumber="");
    /**
    * Finds all addresses specified by a prefix string (the start of the name) and sorts them
    * either by first or last name
    *
    * @param sortBy Optional sorting parameter defaulted to sorting by firstname, can be changed
    * to last name
    */
    void findAddresses(std::string searchedName, NameType sortBy = NameType::FIRSTNAME) const;
};