#include "Features/Creators/Infrastructure/TowerCreator.hpp"

#include "Features/Units/Components/ActionCompletedComponent.hpp"
#include "Features/Units/Components/HealthComponent.hpp"
#include "Features/Units/Conditions/ActionCompletedDeathCondition.hpp"
#include "Features/Units/Conditions/HpDepletedDeathCondition.hpp"
#include "Features/Units/Infrastructure/Unit.hpp"

#include <memory>
#include <utility>
#include <vector>

namespace sw::features
{
    std::unique_ptr<IUnit> TowerCreator::create(
        const TowerCreationData& data
    ) const
    {
        std::vector<Skill> skills;

        skills.push_back(
            _skillFactory.createTowerAimedShot(data.power)
        );

        std::vector<std::unique_ptr<IDeathCondition>> deathConditions;
        deathConditions.push_back(std::make_unique<HpDepletedDeathCondition>());
        deathConditions.push_back(std::make_unique<ActionCompletedDeathCondition>());

        auto unit = std::make_unique<Unit>(
            data.base.unitId,
            data.base.name,
            data.base.position,
            std::move(skills),
            std::move(deathConditions)
        );

        unit->addComponent<HealthComponent>(data.health);
        unit->addComponent<ActionCompletedComponent>();

        return unit;
    }
}
