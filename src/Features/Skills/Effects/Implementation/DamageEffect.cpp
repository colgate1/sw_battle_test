#include "Features/Skills/Effects/Infrastructure/DamageEffect.hpp"

#include "Core/Components/Accessors/ComponentAccess.hpp"
#include "Features/Skills/Data/SkillExecutionContext.hpp"
#include "Features/Units/Components/HealthComponent.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"
#include "IO/Events/UnitAttacked.hpp"

namespace sw::features
{
	DamageEffect::DamageEffect(std::uint32_t value, SkillEffectArea area) :
			ISkillEffect(area),
			_value(value)
	{}

	void DamageEffect::apply(SkillExecutionContext& context) const
	{
		if (context.targetIds.empty())
			return;

		const std::size_t targetsCount =
			area() == SkillEffectArea::Target
				? 1
				: context.targetIds.size();
		for (std::size_t index = 0; index < targetsCount; ++index)
		{
			const std::uint32_t targetId = context.targetIds[index];
			IUnit& target = context.playfield.getUnit(targetId);

			if (target.isDead())
			{
				continue;
			}

			HealthComponent* health = sw::core::findComponent<HealthComponent>(target);

			if (health == nullptr)
			{
				continue;
			}

			health->receiveDamage(_value);

			context.eventLog.log(
				context.tick, sw::io::UnitAttacked{context.casterId, targetId, _value, health->value()});
		}
	}
}
