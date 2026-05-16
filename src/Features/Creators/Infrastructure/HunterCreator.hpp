#pragma once

#include <memory>

#include "IUnitCreator.hpp"
#include "../../Skills/Factories/Infrastructure/SkillFactory.hpp"
#include "Features/Units/Data/HunterCreationData.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{
    class HunterCreator final : public IUnitCreator<HunterCreationData>
    {
    public:
        explicit HunterCreator(SkillFactory& skillFactory)
            : _skillFactory(skillFactory)
        {
        }

        std::unique_ptr<IUnit> create(
            const HunterCreationData& data
        ) const override;

    private:
        SkillFactory& _skillFactory;
    };
}