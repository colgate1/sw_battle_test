#pragma once

#include <memory>
#include <string>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Core/Components/IComponent.hpp"
#include "Core/Math/Position.hpp"
#include "Features/Skills/Skill.hpp"
#include "Features/Units/Conditions/IDeathCondition.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{
    class Unit final : public IUnit
    {
    public:
        Unit(
            std::uint32_t id,
            std::string name,
            Position position,
            std::vector<Skill> skills,
            std::vector<std::unique_ptr<IDeathCondition>> deathConditions
        );

        std::uint32_t id() const override;
        std::string name() const override;

        Position position() const override;
        void setPosition(Position position) override;

        bool isDead() const override;
        void markDead() override;
        bool shouldDie() const override;

        const std::vector<Skill>& skills() const override;

        core::IComponent* findComponent(std::type_index type) override;

        const sw::core::IComponent* findComponent(
            std::type_index type
        ) const override;

        template <typename TComponent, typename... TArgs>
        TComponent& addComponent(TArgs&&... args)
        {
            static_assert(
                std::is_base_of_v<sw::core::IComponent, TComponent>,
                "TComponent must derive from sw::core::IComponent"
            );

            auto component = std::make_unique<TComponent>(
                std::forward<TArgs>(args)...
            );

            TComponent& result = *component;

            _components.insert_or_assign(
                std::type_index(typeid(TComponent)),
                std::move(component)
            );

            return result;
        }

    private:
        std::uint32_t _id;
        std::string _name;
        Position _position;

        bool _isDead = false;

        std::vector<Skill> _skills;
    	std::vector<std::unique_ptr<IDeathCondition>> _deathConditions;

        std::unordered_map<
            std::type_index,
            std::unique_ptr<core::IComponent>
        > _components;
    };
}