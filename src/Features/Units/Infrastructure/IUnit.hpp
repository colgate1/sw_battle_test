#pragma once

#include <string>
#include <vector>

#include "Core/Components/Providers/IComponentProvider.hpp"
#include "Core/Math/Position.hpp"

namespace sw::features
{
    class Skill;

    class IUnit : public sw::core::IComponentProvider
    {
    public:
        virtual ~IUnit() = default;

        virtual std::uint32_t id() const = 0;
        virtual std::string name() const = 0;

        virtual Position position() const = 0;
        virtual void setPosition(Position position) = 0;

        virtual bool isDead() const = 0;
        virtual void markDead() = 0;
        virtual bool shouldDie() const = 0;

        virtual const std::vector<Skill>& skills() const = 0;
    };
}