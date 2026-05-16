#pragma once

#include "Core/Condition/ICondition.hpp"
#include "Features/Skills/Data/TargetContext.hpp"

namespace sw::features
{
    using ITargetCondition = core::ICondition<TargetContext>;
}
