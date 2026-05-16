#pragma once

#include "IBattleActionProcessor.hpp"
#include "Features/BattleSimulation/Data/BattleActionContext.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::features
{
    class MoveProcessor final : public IBattleActionProcessor
    {
    public:
        explicit MoveProcessor(sw::EventLog& eventLog);

        bool canProcess(
            const BattleActionContext& context
        ) const override;

        bool process(
            BattleActionContext& context
        ) const override;

    private:
        EventLog& _eventLog;
    };
}