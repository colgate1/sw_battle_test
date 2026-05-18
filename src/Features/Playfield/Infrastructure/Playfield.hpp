#pragma once

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

#include "Core/Math/Position.hpp"
#include "Features/GameGrid/Infrastructure/GameGrid.hpp"
#include "Features/Playfield/Data/PlayfieldSize.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{
    class Playfield final : public IPlayfield
    {
    public:
        void createMap(PlayfieldSize size) override;
        PlayfieldSize getMapSize() const override;

        void spawnUnit(std::unique_ptr<IUnit> unit) override;

        IUnit& getUnit(std::uint32_t unitId) override;
        const IUnit& getUnit(std::uint32_t unitId) const override;

        bool hasNeighbourUnit(std::uint32_t unitId) const override;

        std::vector<std::uint32_t> getAliveUnitIds() const override;

        bool tryMoveUnitTowards(
            std::uint32_t unitId,
            Position target
        ) override;

    private:
        void ensureMapCreated() const;

        bool ensureInsideMap(Position position) const;
        bool ensureCellIsFree(Position position) const;

        Position chooseNextPositionTowards(
            Position from,
            Position target
        ) const;

        bool canMoveUnitTo(
            std::uint32_t unitId,
            Position position
        ) const;

        bool hasUnitAt(Position position) const;

    private:
        std::optional<GameGrid> _map;

        std::unordered_map<
            std::uint32_t,
            std::unique_ptr<IUnit>
        > _units;
    };
}