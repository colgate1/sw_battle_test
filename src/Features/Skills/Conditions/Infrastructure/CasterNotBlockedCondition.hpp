#pragma once
#include "ISkillCondition.hpp"

namespace sw::features
{
    class CasterNotBlockedCondition final : public ISkillCondition
    {
    public:
        bool isSatisfied(const SkillContext& context) const override;
    };
}
