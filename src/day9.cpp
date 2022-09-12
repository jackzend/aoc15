#include "utils/utils.h"
#include <unordered_map>
struct Edge
{
    std::string_view to_key_;
    int weight_;
};

using AdjList = std::unordered_map<std::string_view, std::vector<Edge>>;

AdjList buildAdjList(const std::vector<std::string_view> &lines)
{
    AdjList ret;

    for (const auto &line : lines)
    {
        auto tokens = utils::SVSplit(line, ' ');
        Edge e{tokens[2], std::stoi(std::string(tokens[4]))};
        if (!utils::mapContains(ret, tokens[0]))
        {
            ret[tokens[0]] = std::vector<Edge>{};
        }
        ret[tokens[0]].push_back(e);
    }
    return ret;
}

void printAdjList(const AdjList &lists)
{
    for (const auto &[k, v] : lists)
    {
        for (const auto &edge : v)
        {
            std::cout << k << " " << edge.to_key_ << ": " << edge.weight_ << "\n";
        }
    }
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

    auto adj_lists = buildAdjList(lines);

    printAdjList(adj_lists);
    // std::cout << "Part 1: " << sum1 << "\n";
    // std::cout << "Part 2: " << sum2 << "\n";
    std::cout << "Time Elapsed: " << timer.getElapsed() << "ms\n";
}