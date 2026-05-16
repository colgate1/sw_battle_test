#include "Features/Skills/Conditions/Infrastructure/CasterNotBlockedCondition.hpp"

#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Skills/Data/SkillContext.hpp"

namespace sw::features
{
    bool CasterNotBlockedCondition::isSatisfied(
        const SkillContext& context
    ) const
    {
        return !context.playfield.hasNeighbourUnit(context.casterId);
    }
}