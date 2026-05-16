#pragma once

#include <algorithm>
#include <cstdint>

struct Position
{
    uint32_t x{};
    uint32_t y{};

    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Position& other) const
    {
        return !(*this == other);
    }

    uint32_t DistanceTo(const Position& other) const
    {
        const uint32_t dx = x > other.x
            ? x - other.x
            : other.x - x;

        const uint32_t dy = y > other.y
            ? y - other.y
            : other.y - y;

        return std::max(dx, dy);
    }
};