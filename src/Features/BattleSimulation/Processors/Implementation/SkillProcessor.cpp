#include "Features/BattleSimulation/Processors/Infrastructure/SkillProcessor.hpp"

#include <random>
#include <utility>
#include <vector>

#include "Features/BattleSimulation/Data/BattleActionContext.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Skills/Data/SkillContext.hpp"
#include "Features/Skills/Data/SkillExecutionContext.hpp"
#include "Features/Skills/Effects/Infrastructure/ISkillEffect.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace
{
    std::uint32_t selectRandomTarget(
        std::mt19937& randomEngine,
        const std::vector<std::uint32_t>& targets
    )
    {
        std::uniform_int_distribution<std::size_t> distribution(
            0,
            targets.size() - 1
        );

        const std::size_t index = distribution(randomEngine);
        return targets[index];
    }

    std::vector<std::uint32_t> selectTargets(
        sw::features::SkillTargetSelection selection,
        std::mt19937& randomEngine,
        const std::vector<std::uint32_t>& targets
    )
    {
        if (selection == sw::features::SkillTargetSelection::RandomSingle)
        {
            return std::vector<std::uint32_t>{
                selectRandomTarget(randomEngine, targets)
            };
        }

        return targets;
    }
}

namespace sw::features
{
    SkillProcessor::SkillProcessor(EventLog& eventLog)
        : SkillProcessor(eventLog, std::mt19937{std::random_device{}()})
    {
    }

    SkillProcessor::SkillProcessor(
        EventLog& eventLog,
        std::mt19937 randomEngine
    )
        : _eventLog(eventLog)
        , _randomEngine(std::move(randomEngine))
    {
    }

    bool SkillProcessor::canProcess(
        const BattleActionContext& context
    ) const
    {
        const IPlayfield& playfield = context.playfield();
        const std::uint32_t casterId = context.unitId();

        const IUnit& caster = playfield.getUnit(casterId);

        if (caster.isDead())
            return false;

        for (const Skill& skill : caster.skills())
        {
            if (canExecute(skill, casterId, playfield))
                return true;
        }

        return false;
    }

    bool SkillProcessor::process(
        BattleActionContext& context
    ) const
    {
        IPlayfield& playfield = context.mutablePlayfield();
        const std::uint32_t casterId = context.unitId();

        const IUnit& caster = playfield.getUnit(casterId);

        if (caster.isDead())
            return false;

        for (const Skill& skill : caster.skills())
        {
            if (tryExecute(skill, casterId, playfield, context.tick()))
                return true;
        }

        return false;
    }

    bool SkillProcessor::canExecute(
        const Skill& skill,
        std::uint32_t casterId,
        const IPlayfield& playfield
    ) const
    {
        SkillContext skillContext{
            casterId,
            playfield
        };

        if (!checkSkillConditions(skill, skillContext))
            return false;

        const std::vector<std::uint32_t> targets = findValidTargets(
            skill,
            skillContext
        );

        return !targets.empty();
    }

    bool SkillProcessor::tryExecute(
        const Skill& skill,
        std::uint32_t casterId,
        IPlayfield& playfield,
        std::uint32_t tick
    ) const
    {
        SkillContext skillContext{
            casterId,
            playfield
        };

        if (!checkSkillConditions(skill, skillContext))
            return false;

        std::vector<std::uint32_t> targets = findValidTargets(
            skill,
            skillContext
        );

        if (targets.empty())
            return skill.completesWithoutTargets();

        targets = selectTargets(skill.targetSelection(), _randomEngine, targets);

        SkillExecutionContext executionContext{
            casterId,
            std::move(targets),
            playfield,
            _eventLog,
            tick
        };

        applyEffects(skill, executionContext);

        return true;
    }

    bool SkillProcessor::checkSkillConditions(
        const Skill& skill,
        const SkillContext& context
    ) const
    {
        for (const auto& condition : skill.skillConditions())
        {
            if (!condition->isSatisfied(context))
                return false;
        }

        return true;
    }

    std::vector<std::uint32_t> SkillProcessor::findValidTargets(
        const Skill& skill,
        const SkillContext& context
    ) const
    {
        std::vector<std::uint32_t> result;

        for (std::uint32_t targetId : context.playfield.getAliveUnitIds())
        {
            if (targetId == context.casterId)
                continue;

            TargetContext targetContext{
                context,
                targetId
            };

            if (!isTargetValid(skill, targetContext))
                continue;

            result.push_back(targetId);
        }

        return result;
    }

    bool SkillProcessor::isTargetValid(
        const Skill& skill,
        const TargetContext& context
    )
    {
        for (const auto& condition : skill.targetConditions())
        {
            if (!condition->isSatisfied(context))
                return false;
        }

        return true;
    }

    void SkillProcessor::applyEffects(
        const Skill& skill,
        SkillExecutionContext& context
    ) const
    {
        for (const auto& effect : skill.effects())
        {
            effect->apply(context);
        }
    }
}
