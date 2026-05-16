#pragma once

#include <cstdint>
#include <vector>

#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::features
{
    struct SkillExecutionContext
    {
        std::uint32_t casterId;
        std::vector<std::uint32_t> targetIds;

        IPlayfield& playfield;
        EventLog& eventLog;
        std::uint32_t tick;
    };
}