#include "utils.h"

void leftTrimInPlace(std::string &str)
{
    str.erase(
        str.begin(),
        std::find_if(str.begin(), str.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        })
    );
};

std::string leftTrim(std::string str)
{
    leftTrimInPlace(str);
    return str;
};