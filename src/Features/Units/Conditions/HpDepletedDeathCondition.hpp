#pragma once

#include "Core/Components/Accessors/ComponentAccess.hpp"
#include "Features/Units/Components/HealthComponent.hpp"
#include "IDeathCondition.hpp"

namespace sw::features
{
    class HpDepletedDeathCondition final : public IDeathCondition
    {
    public:
        bool isSatisfied(const IUnit& unit) const override
        {
            const HealthComponent* health =
                core::findComponent<HealthComponent>(unit);

            if (health == nullptr)
                return true;

            return health->isDepleted();
        }
    };
}
