#pragma once

#include <cstdint>

#include "Core/Commands/Executors/ICommandExecutor.hpp"
#include "Features/Creators/Infrastructure/IUnitCreator.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "Features/Units/Data/TowerCreationData.hpp"
#include "IO/Commands/SpawnTower.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::features
{
    class SpawnTowerExecutor final
        : public core::ICommandExecutor<io::SpawnTower>
    {
    public:
        SpawnTowerExecutor(
            IPlayfield& playfield,
            const IUnitCreator<TowerCreationData>& creator,
            EventLog& eventLog,
            const std::uint32_t& tick
        );

        void execute(const io::SpawnTower& command) override;

    private:
        IPlayfield& _playfield;
        const IUnitCreator<TowerCreationData>& _creator;
        EventLog& _eventLog;
        const std::uint32_t& _tick;
    };
}
