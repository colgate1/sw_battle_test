#pragma once

#include "Core/Condition/ICondition.hpp"
#include "Features/Skills/Data/SkillContext.hpp"

namespace sw::features
{
    using ISkillCondition = core::ICondition<SkillContext>;
}
