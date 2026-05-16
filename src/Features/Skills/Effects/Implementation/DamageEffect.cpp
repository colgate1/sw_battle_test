#include "Features/Skills/Effects/Infrastructure/DamageEffect.hpp"

#include "Core/Components/Accessors/ComponentAccess.hpp"
#include "Features/Skills/Data/SkillExecutionContext.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"
#include "Features/Units/Stats/HealthComponent.hpp"
#include "IO/Events/UnitAttacked.hpp"

namespace sw::features
{
    DamageEffect::DamageEffect(std::uint32_t value)
        : _value(value)
    {
    }

    void DamageEffect::apply(SkillExecutionContext& context) const
    {
        for (std::uint32_t targetId : context.targetIds)
        {
            IUnit& target = context.playfield.getUnit(targetId);

            if (target.isDead())
                continue;

            HealthComponent* health =
                sw::core::findComponent<HealthComponent>(target);

            if (health == nullptr)
                continue;

            health->receiveDamage(_value);

            context.eventLog.log(
                context.tick,
                sw::io::UnitAttacked{
                    context.casterId,
                    targetId,
                    _value,
                    health->value()
                }
            );
        }
    }
}