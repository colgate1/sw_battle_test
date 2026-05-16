#pragma once

#include "IDeathCondition.hpp"
#include "Core/Components/Accessors/ComponentAccess.hpp"
#include "Features/Units/Stats/HealthComponent.hpp"

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
