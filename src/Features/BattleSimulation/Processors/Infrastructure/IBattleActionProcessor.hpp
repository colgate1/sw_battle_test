#pragma once

#include "Core/Processors/IActionProcessor.hpp"
#include "Features/BattleSimulation/Data/BattleActionContext.hpp"

namespace sw::features
{
    using IBattleActionProcessor =
        core::IActionProcessor<BattleActionContext>;
}