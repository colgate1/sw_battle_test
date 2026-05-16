#pragma once

#include "ISkillEffect.hpp"

namespace sw::features
{
    class DamageEffect final : public ISkillEffect
    {
    public:
        explicit DamageEffect(std::uint32_t value);

        void apply(SkillExecutionContext& context) const override;

    private:
        std::uint32_t _value;
    };
}