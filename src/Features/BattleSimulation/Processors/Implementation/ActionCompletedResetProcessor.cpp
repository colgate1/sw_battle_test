#include "Features/BattleSimulation/Processors/Infrastructure/ActionCompletedResetProcessor.hpp"

#include "Core/Components/Accessors/ComponentAccess.hpp"
#include "Features/BattleSimulation/Data/BattleActionContext.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Units/Components/ActionCompletedComponent.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{

	ActionCompletedResetProcessor::ActionCompletedResetProcessor(EventLog& eventLog) :
			_eventLog(eventLog)
	{}

	bool ActionCompletedResetProcessor::canProcess(const BattleActionContext& context) const
	{
		return true;
	}

	bool ActionCompletedResetProcessor::process(BattleActionContext& context) const
	{
		IPlayfield& playfield = context.mutablePlayfield();

		for (std::uint32_t unitId : playfield.getAliveUnitIds())
		{
			IUnit& unit = playfield.getUnit(unitId);

			ActionCompletedComponent* action = findComponent<ActionCompletedComponent>(unit);

			if (action == nullptr)
			{
				continue;
			}

			action->reset();
		}

		return true;
	}
}
