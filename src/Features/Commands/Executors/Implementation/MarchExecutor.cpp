#include "Features/Commands/Executors/Infrastructure/MarchExecutor.hpp"

#include "Core/Components/Accessors/ComponentAccess.hpp"
#include "Features/Units/Components/MoveComponent.hpp"
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

        march(
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

	bool MarchExecutor::march(
		std::uint32_t unitId,
		std::uint32_t targetX,
		std::uint32_t targetY
	)
    {
    	IUnit& unit = _playfield.getUnit(unitId);

    	if (unit.isDead())
    		return false;

    	MoveComponent* move =
			sw::core::findComponent<MoveComponent>(unit);

    	if (move == nullptr)
    		return false;

    	if (!move->canMove())
    		return false;

    	Position target{
    		targetX,
			targetY
		};

    	if (!_playfield.ensureInsideMap(target))
    		return false;

    	if (unit.position() == target)
    	{
    		move->clearMarch();
    		return false;
    	}

    	move->setMarch(target);

    	return true;
    }
}