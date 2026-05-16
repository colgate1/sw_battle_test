#include "Features/Skills/Conditions/Infrastructure/TargetAliveCondition.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Skills/Data/TargetContext.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{
    bool TargetAliveCondition::isSatisfied(
        const TargetContext& context
    ) const
    {
        const IUnit& target =
            context.skillContext.playfield.getUnit(context.targetId);

        return !target.isDead();
    }
}