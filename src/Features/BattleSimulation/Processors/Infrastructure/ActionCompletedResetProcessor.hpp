#pragma once
#include "Features/BattleSimulation/Data/BattleActionContext.hpp"
#include "IBattleActionProcessor.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::features
{
	class ActionCompletedResetProcessor final : public IBattleActionProcessor
	{
	public:
		explicit ActionCompletedResetProcessor(sw::EventLog& eventLog);
		bool process(BattleActionContext& context) const;
		bool canProcess(const BattleActionContext& context) const override;

	private:
		sw::EventLog& _eventLog;
	};
}
