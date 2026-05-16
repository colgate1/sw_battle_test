#pragma once

#include <cstdint>

#include "Core/Math/Position.hpp"
#include "Features/Playfield/Data/PlayfieldSize.hpp"

namespace sw::features
{
    class GameGrid
    {
    public:
        explicit GameGrid(PlayfieldSize size);

        std::uint32_t width() const;
        std::uint32_t height() const;

        bool contains(Position position) const;

    private:
        PlayfieldSize _size;
    };
}