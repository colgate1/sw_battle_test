#pragma once

#include <cstdint>

#include "Core/Commands/Executors/ICommandExecutor.hpp"
#include "Features/Creators/Infrastructure/IUnitCreator.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Units/Data/HunterCreationData.hpp"
#include "IO/Commands/SpawnHunter.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::features
{
    class SpawnHunterExecutor final
        : public core::ICommandExecutor<io::SpawnHunter>
    {
    public:
        SpawnHunterExecutor(
            IPlayfield& playfield,
            const IUnitCreator<HunterCreationData>& creator,
            EventLog& eventLog,
            const std::uint32_t& tick
        );

        void execute(const io::SpawnHunter& command) override;

    private:
        IPlayfield& _playfield;
        const IUnitCreator<HunterCreationData>& _creator;
        EventLog& _eventLog;
        const std::uint32_t& _tick;
    };
}