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

    const std::unordered_map<std::string, OP> toOP = {{"NONE", OP::NONE}, {"AND", OP::AND}, {"OR", OP::OR}, {"LSHIFT", OP::LSHIFT}, {"RSHIFT", OP::RSHIFT}, {"NOT", OP::NOT}};
    class Wire
    {
    public:
        Wire() : lhs_(), rhs_(), op_(OP::NONE), value_(std::nullopt) {}

        std::variant<std::monostate, Wire *, uint16_t> lhs_;
        std::variant<std::monostate, Wire *, uint16_t> rhs_;

        std::optional<uint16_t> value_;

        OP op_;
    };

    class Day7
    {
    public:
        Day7() = default;

        void parse_input(const std::string &file_path);
        uint16_t part1() { return evaluate(&wire_map_["a"]); }
        uint16_t part2(uint16_t p1_val);

        uint16_t evaluate(Wire *w);

        void resetAll();

    private:
        std::unordered_map<std::string, Wire> wire_map_;
    };
}