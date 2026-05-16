#pragma once

#include <cstdint>

#include "Features/Units/Data/UnitCreationBaseData.hpp"

namespace sw::features
{
    struct HunterCreationData
    {
        UnitCreationBaseData base;

        std::uint32_t health{};
        std::uint32_t strength{};
        std::uint32_t range{};
        std::uint32_t agility{};
    };
}