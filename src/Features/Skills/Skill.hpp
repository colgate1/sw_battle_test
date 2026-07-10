#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Effects/Infrastructure/ISkillEffect.hpp"
#include "Conditions/Infrastructure/ISkillCondition.hpp"
#include "Conditions/Infrastructure/ITargetCondition.hpp"

namespace sw::features
{
    enum class SkillTargetSelection
    {
        First,
        RandomSingle
    };

    class Skill final
    {
    public:
        Skill(
            std::string name,
            std::vector<std::unique_ptr<ISkillCondition>> skillConditions,
            std::vector<std::unique_ptr<ITargetCondition>> targetConditions,
            std::vector<std::unique_ptr<ISkillEffect>> effects,
            SkillTargetSelection targetSelection =
                SkillTargetSelection::First,
            bool completesWithoutTargets = false
        )
            : _name(std::move(name))
            , _skillConditions(std::move(skillConditions))
            , _targetConditions(std::move(targetConditions))
            , _effects(std::move(effects))
            , _targetSelection(targetSelection)
            , _completesWithoutTargets(completesWithoutTargets)
        {
        }

        Skill(Skill&&) noexcept = default;
        Skill& operator=(Skill&&) noexcept = default;

        Skill(const Skill&) = delete;
        Skill& operator=(const Skill&) = delete;

        const std::string& name() const
        {
            return _name;
        }

        const std::vector<std::unique_ptr<ISkillCondition>>& skillConditions() const
        {
            return _skillConditions;
        }

        const std::vector<std::unique_ptr<ITargetCondition>>& targetConditions() const
        {
            return _targetConditions;
        }

        const std::vector<std::unique_ptr<ISkillEffect>>& effects() const
        {
            return _effects;
        }

        SkillTargetSelection targetSelection() const
        {
            return _targetSelection;
        }

        bool completesWithoutTargets() const
        {
            return _completesWithoutTargets;
        }

    private:
        std::string _name;

        std::vector<std::unique_ptr<ISkillCondition>> _skillConditions;
        std::vector<std::unique_ptr<ITargetCondition>> _targetConditions;
        std::vector<std::unique_ptr<ISkillEffect>> _effects;
        SkillTargetSelection _targetSelection = SkillTargetSelection::First;
        bool _completesWithoutTargets = false;
    };
}
