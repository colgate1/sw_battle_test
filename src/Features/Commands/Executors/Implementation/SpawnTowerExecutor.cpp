#include "Features/Commands/Executors/Infrastructure/SpawnTowerExecutor.hpp"

#include <string>
#include <utility>

#include "Core/Math/Position.hpp"
#include "Features/Units/Data/UnitCreationBaseData.hpp"
#include "IO/Events/UnitSpawned.hpp"

namespace sw::features
{
    SpawnTowerExecutor::SpawnTowerExecutor(
        IPlayfield& playfield,
        const IUnitCreator<TowerCreationData>& creator,
        EventLog& eventLog,
        const std::uint32_t& tick
    )
        : _playfield(playfield)
        , _creator(creator)
        , _eventLog(eventLog)
        , _tick(tick)
    {
    }

    void SpawnTowerExecutor::execute(const io::SpawnTower& command)
    {
        TowerCreationData data;

        data.base = UnitCreationBaseData{
            command.Name,
            command.unitId,
            Position{command.x, command.y}
        };

        data.health = command.hp;
        data.power = command.power;

        auto unit = _creator.create(data);

        const std::uint32_t unitId = unit->id();
        const std::string unitName = unit->name();
        const Position position = unit->position();

        _playfield.spawnUnit(std::move(unit));

        _eventLog.log(
            _tick,
            io::UnitSpawned{
                unitId,
                unitName,
                position.x,
                position.y
            }
        );
    }
}
