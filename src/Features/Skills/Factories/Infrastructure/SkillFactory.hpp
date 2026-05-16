#pragma once
#include "Features/Skills/Skill.hpp"

namespace sw::features
{
    class SkillFactory final
    {
    public:
        static Skill createSwordsmanAttack(std::uint32_t strength);

        static Skill createHunterShot(
            std::uint32_t agility,
            std::uint32_t range
        );

        static Skill createShadowStrike(std::uint32_t strength);
    };
}