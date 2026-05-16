#pragma once

#include <memory>
#include <vector>

#include "Core/Math/Position.hpp"
#include "Features/Playfield/Data/PlayfieldSize.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{
    class IPlayfield
    {
    public:
        virtual ~IPlayfield() = default;

        virtual void createMap(PlayfieldSize size) = 0;
        virtual PlayfieldSize getMapSize() const = 0;

        virtual void spawnUnit(std::unique_ptr<IUnit> unit) = 0;

        virtual IUnit& getUnit(std::uint32_t unitId) = 0;
        virtual const IUnit& getUnit(std::uint32_t unitId) const = 0;

        virtual bool hasNeighbourUnit(std::uint32_t unitId) const = 0;

        virtual std::vector<std::uint32_t> getAliveUnitIds() const = 0;

        virtual bool tryMoveUnitTowards(
            std::uint32_t unitId,
            Position target
        ) = 0;

        virtual bool march(
            std::uint32_t unitId,
            std::uint32_t targetX,
            std::uint32_t targetY
        ) = 0;
    };
}