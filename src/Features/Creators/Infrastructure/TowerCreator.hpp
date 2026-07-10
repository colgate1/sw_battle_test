#pragma once

#include <memory>

#include "IUnitCreator.hpp"
#include "../../Skills/Factories/Infrastructure/SkillFactory.hpp"
#include "Features/Units/Data/TowerCreationData.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{
    class TowerCreator final : public IUnitCreator<TowerCreationData>
    {
    public:
        explicit TowerCreator(SkillFactory& skillFactory)
            : _skillFactory(skillFactory)
        {
        }

        std::unique_ptr<IUnit> create(
            const TowerCreationData& data
        ) const override;

    private:
        SkillFactory& _skillFactory;
    };
}
