#include "Features/Playfield/Infrastructure/Playfield.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace sw::features
{
    void Playfield::createMap(PlayfieldSize size)
    {
        _map.emplace(size);
    }

	PlayfieldSize Playfield::getMapSize() const
    {
    	ensureMapCreated();

    	return PlayfieldSize{
    		_map->width(),
			_map->height()
		};
    }

    void Playfield::spawnUnit(std::unique_ptr<IUnit> unit)
    {
        if (unit == nullptr)
            throw std::runtime_error("Cannot spawn null unit");

        ensureMapCreated();

        if (!ensureInsideMap(unit->position()))
            throw std::runtime_error("Unit position is outside map");

        if (!ensureCellIsFree(unit->position()))
            throw std::runtime_error("Unit position is occupied");

        const auto unitId = unit->id();

        if (_units.contains(unitId))
            throw std::runtime_error("Unit with this id already exists");

        _units.emplace(unitId, std::move(unit));
    }

    IUnit& Playfield::getUnit(std::uint32_t unitId)
    {
        auto it = _units.find(unitId);

        if (it == _units.end())
            throw std::runtime_error("Unit not found");

        return *it->second;
    }

    const IUnit& Playfield::getUnit(std::uint32_t unitId) const
    {
        auto it = _units.find(unitId);

        if (it == _units.end())
            throw std::runtime_error("Unit not found");

        return *it->second;
    }

    void Playfield::ensureMapCreated() const
    {
        if (!_map.has_value())
            throw std::runtime_error("Map was not created");
    }

    bool Playfield::ensureInsideMap(Position position) const
    {
        return _map->contains(position);
    }

    bool Playfield::ensureCellIsFree(Position position) const
    {
        for (const auto& [unitId, unit] : _units)
        {
            if (unit->position() == position && !unit->isDead())
                return false;
        }

        return true;
    }

    std::vector<std::uint32_t> Playfield::getAliveUnitIds() const
    {
        std::vector<std::uint32_t> result;

        for (const auto& [unitId, unit] : _units)
        {
            if (!unit->isDead())
                result.push_back(unitId);
        }

        std::sort(result.begin(), result.end());

        return result;
    }

    bool Playfield::hasNeighbourUnit(std::uint32_t unitId) const
    {
        const IUnit& unit = getUnit(unitId);
        const Position position = unit.position();

        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;

                const int neighbourX = static_cast<int>(position.x) + dx;
                const int neighbourY = static_cast<int>(position.y) + dy;

                if (neighbourX < 0 || neighbourY < 0)
                    continue;

                const Position neighbour{
                    static_cast<std::uint32_t>(neighbourX),
                    static_cast<std::uint32_t>(neighbourY)
                };

                if (!ensureInsideMap(neighbour))
                    continue;

                if (!ensureCellIsFree(neighbour))
                    return true;
            }
        }

        return false;
    }

    bool Playfield::tryMoveUnitTowards(
        std::uint32_t unitId,
        Position target
    )
    {
        IUnit& unit = getUnit(unitId);

        const Position current = unit.position();

        if (current == target)
            return false;

        Position next = current;

        if (current.x < target.x)
            next.x += 1;
        else if (current.x > target.x)
            next.x -= 1;

        if (current.y < target.y)
            next.y += 1;
        else if (current.y > target.y)
            next.y -= 1;

        if (!canMoveUnitTo(unitId, next))
            return false;

        unit.setPosition(next);

        return true;
    }

    Position Playfield::chooseNextPositionTowards(
        Position from,
        Position target
    ) const
    {
        Position result = from;

        if (from.x < target.x)
        {
            result.x += 1;
            return result;
        }

        if (from.x > target.x)
        {
            result.x -= 1;
            return result;
        }

        if (from.y < target.y)
        {
            result.y += 1;
            return result;
        }

        if (from.y > target.y)
        {
            result.y -= 1;
            return result;
        }

        return result;
    }

    bool Playfield::canMoveUnitTo(
        std::uint32_t unitId,
        Position position
    ) const
    {
        if (!_map->contains(position))
            return false;

        const IUnit& unit = getUnit(unitId);

        if (unit.position() == position)
            return true;

        if (hasUnitAt(position))
            return false;

        return true;
    }

    bool Playfield::hasUnitAt(Position position) const
    {
        for (const auto& [unitId, unit] : _units)
        {
            if (unit->isDead())
                continue;

            if (unit->position() == position)
                return true;
        }

        return false;
    }
}
