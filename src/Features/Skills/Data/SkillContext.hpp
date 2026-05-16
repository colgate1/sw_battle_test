#pragma once

#include "Features/Playfield/Infrastructure/IPlayfield.hpp"

namespace sw::features
{
    struct SkillContext
    {
        std::uint32_t casterId;
        const IPlayfield& playfield;
    };
}