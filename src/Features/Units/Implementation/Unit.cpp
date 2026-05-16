#include "Features/Units/Infrastructure/Unit.hpp"

#include <utility>

namespace sw::features
{
    Unit::Unit(
        std::uint32_t id,
        std::string name,
        Position position,
        std::vector<Skill> skills,
        std::unique_ptr<IDeathCondition> deathCondition
    )
        : _id(id)
        , _name(std::move(name))
        , _position(position)
        , _skills(std::move(skills))
        , _deathCondition(std::move(deathCondition))
    {
    }

    std::uint32_t Unit::id() const
    {
        return _id;
    }

    std::string Unit::name() const
    {
        return _name;
    }

    Position Unit::position() const
    {
        return _position;
    }

    void Unit::setPosition(Position position)
    {
        _position = position;
    }

    bool Unit::isDead() const
    {
        return _isDead;
    }

    void Unit::markDead()
    {
        _isDead = true;
    }

    bool Unit::shouldDie() const
    {
        if (_deathCondition == nullptr)
            return false;

        return _deathCondition->isSatisfied(*this);
    }

    const std::vector<Skill>& Unit::skills() const
    {
        return _skills;
    }

    sw::core::IComponent* Unit::findComponent(std::type_index type)
    {
        const auto it = _components.find(type);

        if (it == _components.end())
            return nullptr;

        return it->second.get();
    }

    const sw::core::IComponent* Unit::findComponent(
        std::type_index type
    ) const
    {
        const auto it = _components.find(type);

        if (it == _components.end())
            return nullptr;

        return it->second.get();
    }
}