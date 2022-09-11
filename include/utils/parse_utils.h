#ifndef PARSE_UTILS_H
#define PARSE_UTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <mio/mmap.hpp>
#include <string_view>
#include <memory>

namespace utils
{

    std::unique_ptr<mio::mmap_source> getMmapFromFile(const std::string &fp)
    {
        const int fd = open(fp.c_str(), O_RDONLY);
        return std::move(std::make_unique<mio::mmap_source>(fd, 0, mio::map_entire_file));
    }

    std::string_view getSVFromMmap(mio::mmap_source *mmap_ptr)
    {
        return std::string_view(mmap_ptr->begin(), mmap_ptr->size());
    }

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