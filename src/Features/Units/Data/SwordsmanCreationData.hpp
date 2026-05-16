#pragma once
#include "Features/Units/Data/UnitCreationBaseData.hpp"

namespace sw::features
{
    struct SwordsmanCreationData
    {
        UnitCreationBaseData base;

        std::uint32_t health{};
        std::uint32_t strength{};
    };
}