#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "Features/Skills/Conditions/Infrastructure/ISkillCondition.hpp"
#include "Features/Skills/Skill.hpp"

namespace sw::features
{
    class SkillBuilder final
    {
    public:
        SkillBuilder& withName(std::string name)
        {
            _name = std::move(name);
            return *this;
        }

        SkillBuilder& withTargetSelection(SkillTargetSelection targetSelection)
        {
            _targetSelection = targetSelection;
            return *this;
        }

        SkillBuilder& completesWithoutTargets(bool value = true)
        {
            _completesWithoutTargets = value;
            return *this;
        }

        template <typename TCondition, typename... TArgs>
        SkillBuilder& addSkillCondition(TArgs&&... args)
        {
            static_assert(
                std::is_base_of_v<ISkillCondition, TCondition>,
                "TCondition must derive from ISkillCondition"
            );

            _skillConditions.push_back(
                std::make_unique<TCondition>(
                    std::forward<TArgs>(args)...
                )
            );

            return *this;
        }

        template <typename TCondition, typename... TArgs>
        SkillBuilder& addTargetCondition(TArgs&&... args)
        {
            static_assert(
                std::is_base_of_v<ITargetCondition, TCondition>,
                "TCondition must derive from ITargetCondition"
            );

            _targetConditions.push_back(
                std::make_unique<TCondition>(
                    std::forward<TArgs>(args)...
                )
            );

            return *this;
        }

        template <typename TEffect, typename... TArgs>
        SkillBuilder& addEffect(TArgs&&... args)
        {
            static_assert(
                std::is_base_of_v<ISkillEffect, TEffect>,
                "TEffect must derive from ISkillEffect"
            );

            _effects.push_back(
                std::make_unique<TEffect>(
                    std::forward<TArgs>(args)...
                )
            );

            return *this;
        }

        Skill build()
        {
            return Skill(
                std::move(_name),
                std::move(_skillConditions),
                std::move(_targetConditions),
                std::move(_effects),
                _targetSelection,
                _completesWithoutTargets
            );
        }

    private:
        std::string _name;
        SkillTargetSelection _targetSelection = SkillTargetSelection::First;
        bool _completesWithoutTargets = false;

        std::vector<std::unique_ptr<ISkillCondition>> _skillConditions;
        std::vector<std::unique_ptr<ITargetCondition>> _targetConditions;
        std::vector<std::unique_ptr<ISkillEffect>> _effects;
    };
}
