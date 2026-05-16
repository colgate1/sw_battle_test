#pragma once
#include <memory>
#include <vector>

#include "Features/BattleSimulation/Processors/Infrastructure/IBattleActionProcessor.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"

namespace sw::features
{
    class BattleSimulation final
    {
    public:
        BattleSimulation(
            IPlayfield& playfield,
            std::vector<std::unique_ptr<IBattleActionProcessor>> turnActiveProcessors,
            std::vector<std::unique_ptr<IBattleActionProcessor>> turnEndProcessors,
            std::uint32_t& tick
        );

        void process();

    private:
        void processTurn(std::uint32_t unitId);
        void processTurnEnd(std::uint32_t unitId);

        bool endSimulation() const;

    private:
        IPlayfield& _playfield;

        std::vector<std::unique_ptr<IBattleActionProcessor>> _turnActiveProcessors;
        std::vector<std::unique_ptr<IBattleActionProcessor>> _turnEndProcessors;

        std::uint32_t& _tick;
    };
}