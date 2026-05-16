#include "Features/Skills/Conditions/Infrastructure/TargetInRangeCondition.hpp"
#include "Core/Math/Position.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Skills/Data/TargetContext.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{
    TargetInRangeCondition::TargetInRangeCondition(std::uint32_t range)
        : _range(range)
    {
    }

    bool TargetInRangeCondition::isSatisfied(
        const TargetContext& context
    ) const
    {
        const auto& playfield = context.skillContext.playfield;

        const auto& caster = playfield.getUnit(
            context.skillContext.casterId
        );

        const auto& target = playfield.getUnit(
            context.targetId
        );

        const std::uint32_t distance =
            caster.position().DistanceTo(target.position());

        return distance <= _range;
    }
}