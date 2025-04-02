#ifndef SCHOOLDATA_H
#define SCHOOLDATA_H

#include <string>

struct SchoolData
{
    std::string name;
    std::string address;
    std::string city;
    std::string state;
    std::string county;


    // Constructor
    SchoolData(std::string n, std::string a, std::string c, std::string s, std::string co)
        : name(n), address(a), city(c), state(s), county(co) {}

#pragma region OperatorOverloads
    /*  /// when you use the > or < operators on strings, the comparison is
        /// lexicographical, which means it compares the strings char by char
        /// based on ASCII values. To use my templated h file, i need to
        /// override the > and <  to define how the comparison is made
        ///
        /// These 3 methods compare names case-insensitively and ignoring spaces
    */

    bool operator<(const SchoolData& other) const
    {
        return normalizedString(name) < normalizedString(other.name);
    }

    bool operator>(const SchoolData& other) const
    {
        return normalizedString(name) > normalizedString(other.name);
    }

    bool operator==(const SchoolData& other) const
    {
        return normalizedString(name) == normalizedString(other.name);
    }

    // Overload the << operator to print the details of SchoolData
    friend std::ostream& operator<<(std::ostream& os, const SchoolData& school)
    {
        os << "Name: " << school.name << ", Address: " << school.address
            << ", City: " << school.city << ", State: " << school.state
            << ", County: " << school.county << std::endl;
        return os;
    };
#pragma endregion


#pragma region Helper
    static std::string normalizedString(const std::string& str)
    {
        std::string result;
        for (char ch : str)
        {
            if (std::isalpha(ch))  //include only alphabetic characters
            {
                result += std::tolower(ch);  //convert to lowercase
            }
        }
        return result;
    }
#pragma endregion
};

#endif
