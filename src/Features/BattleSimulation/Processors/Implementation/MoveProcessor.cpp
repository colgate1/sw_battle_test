#include "Features/BattleSimulation/Processors/Infrastructure/MoveProcessor.hpp"

#include "Core/Components/Accessors/ComponentAccess.hpp"
#include "Core/Math/Position.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Units/Components/MoveComponent.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"
#include "IO/Events/UnitMoved.hpp"

namespace
{
    sw::features::MoveComponent* getValidMoveComponent(
        sw::features::IUnit& unit
    )
    {
        if (unit.isDead())
            return nullptr;

        auto* move =
            sw::core::findComponent<sw::features::MoveComponent>(unit);

        if (move == nullptr || !move->canMove())
            return nullptr;

        return move;
    }

    const sw::features::MoveComponent* getValidMoveComponent(
        const sw::features::IUnit& unit
    )
    {
        if (unit.isDead())
            return nullptr;

        const auto* move =
            sw::core::findComponent<sw::features::MoveComponent>(unit);

        if (move == nullptr || !move->canMove())
            return nullptr;

        return move;
    }
}

namespace sw::features
{
    MoveProcessor::MoveProcessor(EventLog& eventLog)
        : _eventLog(eventLog)
    {
    }

    bool MoveProcessor::canProcess(
        const BattleActionContext& context
    ) const
    {
        const IUnit& unit =
            context.playfield().getUnit(context.unitId());

        const MoveComponent* move = getValidMoveComponent(unit);

        if (move == nullptr)
            return false;

        Position target;

        return move->tryGetMarchTarget(target) &&
               unit.position() != target;
    }

    bool MoveProcessor::process(
        BattleActionContext& context
    ) const
    {
        IPlayfield& playfield = context.mutablePlayfield();
        IUnit& unit = playfield.getUnit(context.unitId());

        MoveComponent* move = getValidMoveComponent(unit);

        if (move == nullptr)
            return false;

        Position target;

        if (!move->tryGetMarchTarget(target))
            return false;

        bool movedAtLeastOnce = false;

        for (std::uint32_t step = 0; step < move->stepsPerTurn(); ++step)
        {
            if (unit.position() == target)
            {
                move->clearMarch();
                return movedAtLeastOnce;
            }

            const bool moved = playfield.tryMoveUnitTowards(
                unit.id(),
                target
            );

            if (!moved)
                return movedAtLeastOnce;

            movedAtLeastOnce = true;

            const Position newPosition = unit.position();

            _eventLog.log(
                context.tick(),
                sw::io::UnitMoved{
                    unit.id(),
                    newPosition.x,
                    newPosition.y
                }
            );
        }

        if (unit.position() == target)
            move->clearMarch();

        return movedAtLeastOnce;
    }
}