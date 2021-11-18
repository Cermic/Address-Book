#include <string>
#include <algorithm>

class Utility {
    public:
    /** 
     * Utility function to return a string converted to lower case. This facilitates
     * case insensitive string comparisons
    */
        static std::string toLower(const std::string stringToConvert) {
        std::string convertedString = stringToConvert; 
        std::transform(convertedString.begin(), convertedString.end(), convertedString.begin(),
            [](unsigned char c){ return std::tolower(c); }
        );
        return convertedString;
    }
};