#include "Features/Skills/Factories/Infrastructure/SkillFactory.hpp"

#include "Features/Skills/Builders/SkillBuilder.hpp"

#include "Features/Skills/Conditions/Infrastructure/TargetInRangeCondition.hpp"
#include "Features/Skills/Conditions/Infrastructure/TargetDistanceRangeCondition.hpp"
#include "../../Conditions/Infrastructure/CasterNotBlockedCondition.hpp"
#include "../../Conditions/Infrastructure/TargetAliveCondition.hpp"
#include "../../Effects/Infrastructure/DamageEffect.hpp"

namespace sw::features
{
    Skill SkillFactory::createSwordsmanAttack(
        std::uint32_t strength
    )
    {
        return SkillBuilder()
            .withName("Swordsman Attack")
            .addTargetCondition<TargetAliveCondition>()
            .addTargetCondition<TargetInRangeCondition>(1)
    		.addEffect<DamageEffect>(strength, SkillEffectArea::Target)
            .build();
    }

    Skill SkillFactory::createHunterShot(
        std::uint32_t agility,
        std::uint32_t range
    )
    {
        return SkillBuilder()
            .withName("Hunter Shot")
            .addSkillCondition<CasterNotBlockedCondition>()
            .addTargetCondition<TargetAliveCondition>()
            .addTargetCondition<TargetInRangeCondition>(range)
            .addEffect<DamageEffect>(agility, SkillEffectArea::Target)
            .build();
    }

    Skill SkillFactory::createShadowStrike(
        std::uint32_t strength
    )
    {
        return SkillBuilder()
            .withName("Shadow Strike")
            .addTargetCondition<TargetAliveCondition>()
            .addTargetCondition<TargetInRangeCondition>(1)
            .addEffect<DamageEffect>(strength, SkillEffectArea::Target)
            .build();
    }

    Skill SkillFactory::createTowerAimedShot(
        std::uint32_t power
    )
    {
        return SkillBuilder()
            .withName("Aimed Shot")
            .withTargetSelection(SkillTargetSelection::RandomSingle)
            .completesWithoutTargets()
            .addTargetCondition<TargetAliveCondition>()
            .addTargetCondition<TargetDistanceRangeCondition>(2, 5)
            .addEffect<DamageEffect>(power, SkillEffectArea::Target)
            .build();
    }
}
