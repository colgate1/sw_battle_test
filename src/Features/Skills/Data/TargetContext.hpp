#pragma once

#include <cstdint>

#include "SkillContext.hpp"

namespace sw::features
{
    struct TargetContext
    {
        const SkillContext& skillContext;
        std::uint32_t targetId;
    };
}
