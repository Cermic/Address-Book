#include "address-book.h"
#include <iostream>

int main () {
    AddressBook addresses;
    std::cout << "Address book is loaded, beginning operations demo: " << std::endl;

    // Initial lookup test
    addresses.retrieveEntries();
    addresses.findAddresses("smi", NameType::LASTNAME);
    // Add some addresses and remove some
    addresses.addAddress("david", "smith");
    addresses.addAddress("david", "smith", "085558337548");
    addresses.addAddress("david", "smith");
    addresses.removeAddress("david", "smit");
    addresses.addAddress("david", "smit");
    addresses.removeAddress("david", "smit");
    addresses.addAddress("david", "smit");
    addresses.addAddress("lang", "he");
    addresses.addAddress("ami", "wen");
    addresses.addAddress("ami", "yu");
    addresses.addAddress("brad", "felt");
    addresses.removeAddress("ami", "yu");
    addresses.addAddress("felt", "brad");
    addresses.addAddress("wayne", "yu");
    addresses.addAddress("ami", "yu", "6869848975");
    addresses.addAddress("fan", "helter");
    addresses.addAddress("rhys", "murray");
    // Lookup addresses
    addresses.retrieveEntries();
    addresses.retrieveEntries(NameType::LASTNAME);
    addresses.findAddresses("aM");
    addresses.findAddresses("smi", NameType::LASTNAME);
    addresses.findAddresses("smithy", NameType::LASTNAME);

    std::cout << "This program cycle is complete, please close the program..." << std::endl;
    std::cin.get();
    return 0;
}