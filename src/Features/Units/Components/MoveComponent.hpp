#pragma once

#include <cstdint>
#include <optional>

#include "Core/Components/IComponent.hpp"
#include "Core/Math/Position.hpp"

namespace sw::features
{
    class MoveComponent final : public sw::core::IComponent
    {
    public:
        explicit MoveComponent(std::uint32_t stepsPerTurn)
            : _stepsPerTurn(stepsPerTurn)
        {
        }

        bool canMove() const
        {
            return _stepsPerTurn > 0;
        }

        std::uint32_t stepsPerTurn() const
        {
            return _stepsPerTurn;
        }

        bool tryGetMarchTarget(Position& outTarget) const
        {
            if (!_marchTarget.has_value())
                return false;

            outTarget = *_marchTarget;
            return true;
        }

        void setMarch(Position target)
        {
            _marchTarget = target;
        }

        void clearMarch()
        {
            _marchTarget.reset();
        }

    private:
        std::uint32_t _stepsPerTurn = 0;
        std::optional<Position> _marchTarget;
    };
}