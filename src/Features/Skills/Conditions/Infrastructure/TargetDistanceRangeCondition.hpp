#pragma once

#include <cstdint>

#include "ITargetCondition.hpp"

namespace sw::features
{
    class TargetDistanceRangeCondition final : public ITargetCondition
    {
    public:
        TargetDistanceRangeCondition(
            std::uint32_t minDistance,
            std::uint32_t maxDistance
        );

        bool isSatisfied(const TargetContext& context) const override;

    private:
        std::uint32_t _minDistance;
        std::uint32_t _maxDistance;
    };
}
