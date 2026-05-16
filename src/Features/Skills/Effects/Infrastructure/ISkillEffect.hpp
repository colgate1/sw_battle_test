#pragma once

#include "Features/Skills/Data/SkillExecutionContext.hpp"
#include "SkillEffectArea.hpp"

namespace sw::features
{
	class ISkillEffect
	{
	public:
		explicit ISkillEffect(SkillEffectArea area)
			: _area(area)
		{
		}

		virtual ~ISkillEffect() = default;

		SkillEffectArea area() const
		{
			return _area;
		}

		virtual void apply(SkillExecutionContext& context) const = 0;

	private:
		SkillEffectArea _area;
	};
}