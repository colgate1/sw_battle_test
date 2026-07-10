#pragma once

#include <cstdint>

#include "Features/Units/Data/UnitCreationBaseData.hpp"

namespace sw::features
{
    struct TowerCreationData
    {
        UnitCreationBaseData base;

        std::uint32_t health{};
        std::uint32_t power{};
    };
}
