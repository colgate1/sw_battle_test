#pragma once

#include "ITargetCondition.hpp"

namespace sw::features
{
    class TargetAliveCondition final : public ITargetCondition
    {
    public:
        bool isSatisfied(const TargetContext& context) const override;
    };
}