#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H

#include <string>
#include <sstream>
#include <vector>

namespace utils
{

    void split(const std::string &s, char delim, std::vector<std::string> &elems)
    {
        std::stringstream ss(s);
        std::string item;
        while (getline(ss, item, delim))
        {
            elems.push_back(item);
        }
    }

    std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

}

#endif