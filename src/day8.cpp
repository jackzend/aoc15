#include <iostream>
#include "utils/utils.h"
#include <mio/mmap.hpp>
#include <string_view>

constexpr char backslash = '\\';
constexpr char quote = '"';

int processStringP1(const std::string_view str)
{
    int code_rep = str.size();
    int in_mem = 0;

    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == quote)
        {
            continue;
        }
        else if (str[i] == backslash)
        {
            ++i;
            if (str[i] == quote or str[i] == backslash)
            {
            }
            else if (str[i] == 'x')
            {
                i += 2;
            }
        }
        ++in_mem;
    }
    return code_rep - in_mem;
}

int processStringP2(const std::string_view str)
{
    int code_rep = str.size();
    int opposite = str.size() + 2;

    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == quote or str[i] == backslash)
        {
            opposite++;
        }
    }
    return opposite - code_rep;
}

int main(int argc, char *argv[])
{
    /** Start Timer */
    utils::MilliSecondTimer timer;

    /** Construct string view of input file */
    auto mmap_ptr = utils::getMmapFromFile(argv[1]);
    std::string_view temp = utils::getSVFromMmap(mmap_ptr.get());

    /** Tokenize lines */
    auto lines = utils::SVSplit(temp, '\n');

    /** Part1 and Part2 */
    int sum1 = 0;
    int sum2 = 0;
    for (const auto line : lines)
    {
        sum1 += processStringP1(line);
        sum2 += processStringP2(line);
    }
    std::cout << "Part 1: " << sum1 << "\n";
    std::cout << "Part 2: " << sum2 << "\n";
    std::cout << "Time Elapsed: " << timer.getElapsed() << "ms\n";
}