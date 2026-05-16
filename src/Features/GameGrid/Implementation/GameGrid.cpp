#include "Features/GameGrid/Infrastructure/GameGrid.hpp"

#include <cstdint>

namespace sw::features
{
    GameGrid::GameGrid(PlayfieldSize size)
        : _size(size)
    {
    }

    std::uint32_t GameGrid::width() const
    {
        return _size.width;
    }

    std::uint32_t GameGrid::height() const
    {
        return _size.height;
    }

    bool GameGrid::contains(Position position) const
    {
        return position.x < _size.width &&
               position.y < _size.height;
    }
}