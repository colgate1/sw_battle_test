#include "Features/Commands/Executors/Infrastructure/SpawnHunterExecutor.hpp"

#include <memory>
#include <string>
#include <utility>

#include "Core/Math/Position.hpp"
#include "Features/Units/Data/UnitCreationBaseData.hpp"
#include "IO/Events/UnitSpawned.hpp"

namespace sw::features
{
    SpawnHunterExecutor::SpawnHunterExecutor(
        IPlayfield& playfield,
        const IUnitCreator<HunterCreationData>& creator,
        EventLog& eventLog,
        const std::uint32_t& tick
    )
        : _playfield(playfield)
        , _creator(creator)
        , _eventLog(eventLog)
        , _tick(tick)
    {
    }

    void SpawnHunterExecutor::execute(
        const io::SpawnHunter& command
    )
    {
        HunterCreationData data;

        data.base = UnitCreationBaseData{
            command.Name,
            command.unitId,
            Position{command.x, command.y}
        };

        data.range = command.range;
        data.agility = command.agility;
        data.health = command.hp;
        data.strength = command.strength;

        auto unit = _creator.create(data);

        const std::uint32_t unitId = unit->id();
        const std::string unitName = unit->name();
        const Position position = unit->position();

        _playfield.spawnUnit(std::move(unit));

        _eventLog.log(
            _tick,
            sw::io::UnitSpawned{
                unitId,
                unitName,
                position.x,
                position.y
            }
        );
    }
}