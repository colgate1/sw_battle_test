#pragma once

#include <cstdint>

#include "Core/Components/IComponent.hpp"

namespace sw::features
{
    class HealthComponent final : public sw::core::IComponent
    {
    public:
        explicit HealthComponent(std::uint32_t health)
            : _health(health)
        {
        }

        std::uint32_t value() const
        {
            return _health;
        }

        void receiveDamage(std::uint32_t damage)
        {
            if (damage >= _health)
            {
                _health = 0;
                return;
            }

            _health -= damage;
        }

        bool isDepleted() const
        {
            return _health == 0;
        }

    private:
        std::uint32_t _health;
    };
}