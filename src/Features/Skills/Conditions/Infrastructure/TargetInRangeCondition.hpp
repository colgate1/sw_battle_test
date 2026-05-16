#pragma once

#include "ITargetCondition.hpp"
#include "Features/Skills/Data/TargetContext.hpp"

namespace sw::features
{
    class TargetInRangeCondition final : public ITargetCondition
    {
    public:
        explicit TargetInRangeCondition(std::uint32_t range);

        bool isSatisfied(const TargetContext& context) const override;

    private:
        std::uint32_t _range;
    };
}
