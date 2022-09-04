
#include <iostream>
#include <chrono>
#include "basic_timer.h"
#include "parse_utils.h"
#include <chrono>
#include <thread>
#include <unordered_set>
#include <optional>
#include <variant>
#include <fstream>

using namespace std::chrono_literals;
namespace day7
{
    enum class OP
    {
        NONE = 0,
        AND,
        OR,
        LSHIFT,
        RSHIFT,
        NOT,
        SZ = 6
    };

    class Wire
    {
    public:
        Wire(const std::string &name) : name_(name), lhs_(), rhs_(), op_(OP::NONE) {}

        std::string name_;

        std::variant<std::monostate, Wire *, uint16_t> lhs_;
        std::variant<std::monostate, Wire *, uint16_t> rhs_;

        OP op_;
    };

    std::unordered_map<std::string, Wire> wire_map;

    void parse_input(const std::string &file_path)
    {
        std::ifstream infile(file_path);

        std::string temp;
        while (getline(infile, temp))
        {
            auto tokens = utils::split(temp);
        }
    }

} // namespace day7

int main()
{
    utils::MilliSecondTimer timer;
    std::cout << "Day 7 P1: " << timer.getElapsed() << std::endl;
    timer.reset();
    std::cout << "Day 7 P2: " << timer.getElapsed() << std::endl;
}