#pragma once

#include <cstdint>

#include "Features/Skills/Effects/Infrastructure/ISkillEffect.hpp"

namespace sw::features
{
	class DamageEffect final : public ISkillEffect
	{
	public:
		DamageEffect(
			std::uint32_t value,
			SkillEffectArea area
		);

		void apply(SkillExecutionContext& context) const override;

	private:
		std::uint32_t _value;
	};
}