#pragma once

#include <cstdint>
#include <string>

#include "Core/Math/Position.hpp"

namespace sw::features
{
    struct UnitCreationBaseData
    {
        std::string name{};
        std::uint32_t unitId{};
        Position position{};
    };
}