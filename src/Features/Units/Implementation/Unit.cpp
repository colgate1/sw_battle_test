#include "Features/Units/Infrastructure/Unit.hpp"

#include <utility>

namespace sw::features
{
    Unit::Unit(
        std::uint32_t id,
        std::string name,
        Position position,
        std::vector<Skill> skills,
        std::vector<std::unique_ptr<IDeathCondition>> deathConditions
    )
        : _id(id)
        , _name(std::move(name))
        , _position(position)
        , _skills(std::move(skills))
        , _deathConditions(std::move(deathConditions))
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
    	for (const auto& condition : _deathConditions)
    	{
    		if (!condition->isSatisfied(*this))
    		{
    			return false;
    		}
    	}

    	return true;
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