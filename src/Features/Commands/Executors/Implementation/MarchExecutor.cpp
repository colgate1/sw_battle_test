#include "Features/Commands/Executors/Infrastructure/MarchExecutor.hpp"

#include "Features/Units/Infrastructure/IUnit.hpp"
#include "IO/Events/MarchStarted.hpp"

namespace sw::features
{
    MarchExecutor::MarchExecutor(
        IPlayfield& playfield,
        EventLog& eventLog,
        const std::uint32_t& tick
    )
        : _playfield(playfield)
        , _eventLog(eventLog)
        , _tick(tick)
    {
    }

    void MarchExecutor::execute(const io::March& command)
    {
        const IUnit& unit = _playfield.getUnit(command.unitId);
        const Position from = unit.position();

        _playfield.march(
            command.unitId,
            command.targetX,
            command.targetY
        );

        _eventLog.log(
            _tick,
            io::MarchStarted{
                command.unitId,
                from.x,
                from.y,
                command.targetX,
                command.targetY
            }
        );
    }
}