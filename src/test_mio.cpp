#include <iostream>
#include <chrono>
#include "utils/utils.h"
#include <chrono>
#include <thread>
#include <unordered_map>
#include <optional>
#include <variant>
#include <fstream>
#include <mio/mmap.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    std::string file_path = "/Users/jackzender/aoc15/input/day7/day7_test.txt";
    std::error_code e;

    const int fd = open(file_path.c_str(), O_RDONLY);
    mio::mmap_source mmap(fd, 0, mio::map_entire_file);
    if (e)
    {
        std::cout << "Error mapping file" << std::endl;
        return -1;
    }

    std::string_view temp(mmap.begin(), mmap.size());

    auto lines = utils::SVSplit(temp, '\n');

    for (const auto &line : lines)
    {
        auto tokens = utils::SVSplit(line, ' ');
        for (const auto word : tokens)
        {
            if (utils::allDigits(word))
            {
                std::cout << word << " ";
            }
        }
        std::cout << "\n";
    }
}