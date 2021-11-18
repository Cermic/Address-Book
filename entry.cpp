#include "entry.h"

const std::string Entry::toString(NameType nameOrder) const {
    std::string outputString = "";
    if (nameOrder == NameType::FIRSTNAME) {
        outputString = "First name: " + firstName +
        "\t Last Name: " + lastName;
    } else {
        outputString = "Last name: " + lastName +
        "\t First Name: " + firstName;
    }
    outputString += phoneNumber.length() > 0 ? "\tPhone Number: " + phoneNumber : "";
    return outputString;
}