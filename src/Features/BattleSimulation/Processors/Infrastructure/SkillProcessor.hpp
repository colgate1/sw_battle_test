#pragma once

#include <vector>

#include "IBattleActionProcessor.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Skills/Skill.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::features
{
    struct SkillExecutionContext;

    class SkillProcessor final : public IBattleActionProcessor
    {
    public:
        explicit SkillProcessor(sw::EventLog& eventLog);

        bool canProcess(
            const BattleActionContext& context
        ) const override;

        bool process(
            BattleActionContext& context
        ) const override;

    private:
        bool canExecute(
            const Skill& skill,
            std::uint32_t casterId,
            const IPlayfield& playfield
        ) const;

        bool tryExecute(
            const Skill& skill,
            std::uint32_t casterId,
            IPlayfield& playfield,
            std::uint32_t tick
        ) const;

        bool checkSkillConditions(
            const Skill& skill,
            const SkillContext& context
        ) const;

        std::vector<std::uint32_t> findValidTargets(
            const Skill& skill,
            const SkillContext& context
        ) const;

        static bool isTargetValid(
            const Skill& skill,
            const TargetContext& context
        );

        void applyEffects(
            const Skill& skill,
            SkillExecutionContext& context
        ) const;

    private:
        EventLog& _eventLog;
    };
}