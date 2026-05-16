#pragma once
#include "Core/Commands/Executors/ICommandExecutor.hpp"
#include "Features/Creators/Infrastructure/IUnitCreator.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Units/Data/SwordsmanCreationData.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::features
{
    class SpawnSwordsmanExecutor final
        : public core::ICommandExecutor<io::SpawnSwordsman>
    {
    public:
        SpawnSwordsmanExecutor(
            IPlayfield& playfield,
            const IUnitCreator<SwordsmanCreationData>& creator,
            EventLog& eventLog,
            const std::uint32_t& tick
        );

        void execute(const io::SpawnSwordsman& command) override;

    private:
        IPlayfield& _playfield;
        const IUnitCreator<SwordsmanCreationData>& _creator;
        EventLog& _eventLog;
        const std::uint32_t& _tick;
    };
}