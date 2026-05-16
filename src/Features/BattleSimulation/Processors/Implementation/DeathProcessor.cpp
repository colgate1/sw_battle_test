#include "Features/BattleSimulation/Processors/Infrastructure/DeathProcessor.hpp"

#include "Features/BattleSimulation/Data/BattleActionContext.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"
#include "IO/Events/UnitDied.hpp"

#include <vector>

namespace sw::features
{
	DeathProcessor::DeathProcessor(sw::EventLog& eventLog) :
			_eventLog(eventLog)
	{}

	bool DeathProcessor::canProcess(const BattleActionContext& context) const
	{
		return true;
	}

	bool DeathProcessor::process(BattleActionContext& context) const
	{
		const std::vector<std::uint32_t> aliveUnitIds = context.playfield().getAliveUnitIds();

		bool killedAtLeastOne = false;

		for (std::uint32_t unitId : aliveUnitIds)
		{
			if (unitId > context.unitId())
			{
				break;
			}

			IUnit& unit = context.mutablePlayfield().getUnit(unitId);

			if (!unit.shouldDie())
			{
				continue;
			}

			unit.markDead();
			killedAtLeastOne = true;

			_eventLog.log(context.tick(), io::UnitDied{unitId});
		}

		return killedAtLeastOne;
	}
}
