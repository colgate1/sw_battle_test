#pragma once

#include "Core/Commands/Executors/ICommandExecutor.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "IO/Commands/March.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::features
{
    class MarchExecutor final
        : public core::ICommandExecutor<io::March>
    {
    public:
        MarchExecutor(
            IPlayfield& playfield,
            EventLog& eventLog,
            const std::uint32_t& tick
        );

        void execute(const io::March& command) override;

    private:
        IPlayfield& _playfield;
        EventLog& _eventLog;
        const std::uint32_t& _tick;
    };
}