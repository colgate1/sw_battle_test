#pragma once


#include "IBattleActionProcessor.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::features
{
    class DeathProcessor final : public IBattleActionProcessor
    {
    public:
        explicit DeathProcessor(sw::EventLog& eventLog);

        bool canProcess(const BattleActionContext& context) const override;
        bool process(BattleActionContext& context) const override;

    private:
        sw::EventLog& _eventLog;
    };
}