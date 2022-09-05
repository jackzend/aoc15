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

    std::vector<std::string_view> SVSplit(const std::string_view str, const char delim = ',')
    {
        std::vector<std::string_view> result;

        int indexCommaToLeftOfColumn = 0;
        int indexCommaToRightOfColumn = -1;

        for (int i = 0; i < static_cast<int>(str.size()); i++)
        {
            if (str[i] == delim)
            {
                indexCommaToLeftOfColumn = indexCommaToRightOfColumn;
                indexCommaToRightOfColumn = i;
                int index = indexCommaToLeftOfColumn + 1;
                int length = indexCommaToRightOfColumn - index;

                // Bounds checking can be omitted as logically, this code can never be invoked
                // Try it: put a breakpoint here and run the unit tests.
                /*if (index + length >= static_cast<int>(str.size()))
                {
                    length--;
                }
                if (length < 0)
                {
                    length = 0;
                }*/

                std::string_view column(str.data() + index, length);
                result.push_back(column);
            }
        }
        const std::string_view finalColumn(str.data() + indexCommaToRightOfColumn + 1, str.size() - indexCommaToRightOfColumn - 1);
        result.push_back(finalColumn);
        return result;
    }

}

#endif