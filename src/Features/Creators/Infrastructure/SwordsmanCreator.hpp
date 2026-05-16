#pragma once

#include <memory>

#include "IUnitCreator.hpp"
#include "../../Skills/Factories/Infrastructure/SkillFactory.hpp"
#include "Features/Units/Data/SwordsmanCreationData.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{
    class SwordsmanCreator final
        : public IUnitCreator<SwordsmanCreationData>
    {
    public:
        explicit SwordsmanCreator(SkillFactory& skillFactory)
            : _skillFactory(skillFactory)
        {
        }

        std::unique_ptr<IUnit> create(
            const SwordsmanCreationData& data
        ) const override;

    private:
        SkillFactory& _skillFactory;
    };
}