#include <memory>
#include <utility>
#include <vector>

#include "Features/Creators/Infrastructure/HunterCreator.hpp"
#include "Features/Units/Conditions/HpDepletedDeathCondition.hpp"
#include "Features/Units/Infrastructure/Unit.hpp"
#include "Features/Units/Stats/MoveComponent.hpp"

namespace sw::features
{
    std::unique_ptr<IUnit> HunterCreator::create(
        const HunterCreationData& data
    ) const
    {
        std::vector<Skill> skills;

        skills.push_back(
            _skillFactory.createHunterShot(data.agility, data.range)
        );

        skills.push_back(
            _skillFactory.createShadowStrike(data.strength)
        );

        auto unit = std::make_unique<Unit>(
            data.base.unitId,
            data.base.name,
            data.base.position,
            std::move(skills),
            std::make_unique<HpDepletedDeathCondition>()
        );

        unit->addComponent<HealthComponent>(data.health);
        unit->addComponent<MoveComponent>(1);

        return unit;
    }
}
