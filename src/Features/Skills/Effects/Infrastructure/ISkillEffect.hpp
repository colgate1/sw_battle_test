#pragma once

#include "Features/Skills/Data/SkillExecutionContext.hpp"

namespace sw::features
{
    class ISkillEffect
    {
    public:
        virtual ~ISkillEffect() = default;

        virtual void apply(SkillExecutionContext& context) const = 0;
    };
}
