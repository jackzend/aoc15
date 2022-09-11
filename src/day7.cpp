#include "day7.h"
using namespace std::chrono_literals;
namespace day7
{

    void Day7::parse_input(const std::string &file_path)
    {
        const int fd = open(file_path.c_str(), O_RDONLY);
        mio::mmap_source mmap(fd, 0, mio::map_entire_file);
        std::string_view temp(mmap.begin(), mmap.size());

        auto lines = utils::SVSplit(temp, '\n');

        for (const auto temp : lines)
        {
            auto tokens = utils::SVSplit(temp, ' ');
            size_t sz = tokens.size();
            // this is an asignment
            if (sz == 3)
            {
                std::string name(tokens[2]);

                if (!utils::mapContains(wire_map_, name))
                {
                    wire_map_.insert_or_assign(name, Wire());
                }
                wire_map_[name].lhs_ = std::monostate(); // no lhs
                wire_map_[name].op_ = OP::NONE;          // no op

                std::string rhs(tokens[0]);
                std::optional<uint16_t> rhs_i = std::nullopt;
                if (utils::allDigits(rhs))
                {
                    rhs_i.emplace(std::stoi(rhs));
                }
                // the rhs is an integer
                if (rhs_i.has_value())
                {
                    wire_map_[name].rhs_ = rhs_i.value();
                    wire_map_[name].value_ = rhs_i;
                }
                else // rhs is a wire
                {
                    if (!utils::mapContains(wire_map_, rhs))
                    {
                        wire_map_.insert_or_assign(rhs, Wire());
                    }
                    wire_map_[name].rhs_ = &wire_map_[rhs]; // link Wires
                }
            }
            // this is an unary op (only NOT)
            else if (sz == 4)
            {
                std::string name(tokens[3]);

                // check if the name exists
                if (!utils::mapContains(wire_map_, name))
                {
                    wire_map_.insert_or_assign(name, Wire());
                }
                wire_map_[name].lhs_ = std::monostate(); // no lhs
                wire_map_[name].op_ = OP::NOT;

                // get the string to the right of the NOT
                std::string rhs(tokens[1]);
                std::optional<uint16_t> rhs_i = std::nullopt;
                if (utils::allDigits(rhs))
                {
                    rhs_i.emplace(std::stoi(rhs));
                }
                // the rhs is an integer
                if (rhs_i.has_value())
                {
                    wire_map_[name].rhs_ = rhs_i.value();
                }
                else // rhs is a wire
                {
                    if (!utils::mapContains(wire_map_, rhs))
                    {
                        wire_map_.insert_or_assign(rhs, Wire());
                    }
                    wire_map_[name].rhs_ = &wire_map_[rhs]; // link Wires
                }
            }
            // this is a binary op
            else if (sz == 5)
            {
                std::string name(tokens[4]);

                // check if the name exists
                if (!utils::mapContains(wire_map_, name))
                {
                    wire_map_.insert_or_assign(name, Wire());
                }
                wire_map_[name].op_ = toOP.at(std::string(tokens[1]));

                // get the string to the left of the OP
                std::string lhs(tokens[0]);
                std::optional<uint16_t> lhs_i = std::nullopt;
                if (utils::allDigits(lhs))
                {
                    lhs_i.emplace(std::stoi(lhs));
                }
                // the rhs is an integer
                if (lhs_i.has_value())
                {
                    wire_map_[name].lhs_ = lhs_i.value();
                }
                else // lhs is a wire
                {
                    if (!utils::mapContains(wire_map_, lhs))
                    {
                        wire_map_.insert_or_assign(lhs, Wire());
                    }
                    wire_map_[name].lhs_ = &wire_map_[lhs]; // link Wires
                }

                // get the string to the right of the OP
                std::string rhs(tokens[2]);
                std::optional<uint16_t> rhs_i = std::nullopt;
                if (utils::allDigits(rhs))
                {
                    rhs_i.emplace(std::stoi(rhs));
                }
                // the rhs is an integer
                if (rhs_i.has_value())
                {
                    wire_map_[name].rhs_ = rhs_i.value();
                }
                else // lhs is a wire
                {
                    if (!utils::mapContains(wire_map_, rhs))
                    {
                        wire_map_.insert_or_assign(rhs, Wire());
                    }
                    wire_map_[name].rhs_ = &wire_map_[rhs]; // link Wires
                }
            }
        }
    }

    uint16_t Day7::evaluate(Wire *w)
    {
        if (w->value_.has_value())
        {
            return w->value_.value();
        }

        auto visitor = utils::overloaded{
            [](std::monostate &val)
            { return static_cast<uint16_t>(0); },
            [](uint16_t val)
            { return val; },
            [this](Wire *w)
            { return this->evaluate(w); }};

        uint16_t ret = 0;
        switch (w->op_)
        {
        case OP::NONE:
        {
            return std::visit(visitor, w->rhs_);
        }
        case OP::NOT:
        {
            ret = ~(std::visit(visitor, w->rhs_));
            w->value_.emplace(ret);
            return ret;
        }
        case OP::AND:
        {
            uint16_t rhs_i = std::visit(visitor, w->rhs_);
            uint16_t lhs_i = std::visit(visitor, w->lhs_);
            ret = lhs_i & rhs_i;
            w->value_.emplace(ret);
            return ret;
        }
        case OP::OR:
        {
            uint16_t rhs_i = std::visit(visitor, w->rhs_);
            uint16_t lhs_i = std::visit(visitor, w->lhs_);
            ret = lhs_i | rhs_i;
            w->value_.emplace(ret);
            return ret;
        }
        case OP::LSHIFT:
        {
            uint16_t rhs_i = std::visit(visitor, w->rhs_);
            uint16_t lhs_i = std::visit(visitor, w->lhs_);
            ret = lhs_i << rhs_i;
            w->value_.emplace(ret);
            return ret;
        }
        case OP::RSHIFT:
        {
            uint16_t rhs_i = std::visit(visitor, w->rhs_);
            uint16_t lhs_i = std::visit(visitor, w->lhs_);
            ret = lhs_i >> rhs_i;
            w->value_.emplace(ret);
            return ret;
        }
        break;

        default:
            break;
        }
        return 0;
    }

    void Day7::resetAll()
    {
        for (auto &[k, v] : wire_map_)
        {
            v.value_.reset();
        }
    }

    uint16_t Day7::part2(uint16_t p1_val)
    {
        resetAll();
        wire_map_["b"].value_.emplace(p1_val);
        return evaluate(&wire_map_["a"]);
    }

} // namespace day7

int main(int argc, char *argv[])
{
    utils::MilliSecondTimer timer;

    day7::Day7 solution;
    solution.parse_input(std::string(argv[1]));

    // Runs the algorithm
    uint16_t p1 = solution.part1();
    uint16_t p2 = solution.part2(p1);
    float time_elapsed = timer.getElapsed();

    std::cout << "Day 7 P1: " << p1 << " P2: " << p2 << " time elapsed : " << time_elapsed << "ms" << std::endl;
}