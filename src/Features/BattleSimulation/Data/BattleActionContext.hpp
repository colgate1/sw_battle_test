#pragma once

#include <cstdint>

#include "Features/Playfield/Infrastructure/IPlayfield.hpp"

namespace sw::features
{
    class BattleActionContext
    {
    public:
        BattleActionContext(
            std::uint32_t unitId,
            IPlayfield& playfield,
            std::uint32_t tick
        )
            : _unitId(unitId)
            , _tick(tick)
            , _playfield(playfield)
        {
        }

        std::uint32_t unitId() const
        {
            return _unitId;
        }

        std::uint32_t tick() const
        {
            return _tick;
        }

        const IPlayfield& playfield() const
        {
            return _playfield;
        }

        IPlayfield& mutablePlayfield()
        {
            return _playfield;
        }

    private:
        std::uint32_t _unitId;
        std::uint32_t _tick;
        IPlayfield& _playfield;
    };
}