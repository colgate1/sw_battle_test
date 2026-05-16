#include "Features/BattleSimulation/Processors/Infrastructure/DeathProcessor.hpp"
#include <vector>
#include "Features/BattleSimulation/Data/BattleActionContext.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"
#include "IO/Events/UnitDied.hpp"

namespace sw::features
{
    DeathProcessor::DeathProcessor(sw::EventLog& eventLog)
        : _eventLog(eventLog)
    {
    }

    bool DeathProcessor::canProcess(
        const BattleActionContext& context
    ) const
    {
        return true;
    }

    bool DeathProcessor::process(BattleActionContext& context) const
    {
        bool killedAtLeastOne = false;

        const std::vector<std::uint32_t> aliveUnitIds =
            context.playfield().getAliveUnitIds();

        for (std::uint32_t unitId : aliveUnitIds)
        {
            IUnit& unit = context.mutablePlayfield().getUnit(unitId);

            if (!unit.shouldDie())
                continue;

            unit.markDead();
            killedAtLeastOne = true;

            _eventLog.log(
                context.tick(),
                sw::io::UnitDied{
                    unitId
                }
            );
        }

        return killedAtLeastOne;
    }
}