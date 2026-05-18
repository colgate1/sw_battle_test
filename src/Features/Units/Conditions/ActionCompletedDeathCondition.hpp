#pragma once

#include "Core/Components/Accessors/ComponentAccess.hpp"
#include "Features/Units/Components/ActionCompletedComponent.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"
#include "IDeathCondition.hpp"

namespace sw::features
{
	class ActionCompletedDeathCondition final : public IDeathCondition
	{
	public:
		bool isSatisfied(const IUnit& unit) const override
		{
			const ActionCompletedComponent* action =
				core::findComponent<ActionCompletedComponent>(unit);

			return action != nullptr && action->isCompleted();
		}
	};
}