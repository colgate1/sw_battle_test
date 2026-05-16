#pragma once
#include "Core/Commands/Executors/ICommandExecutor.hpp"
#include "Features/Playfield/Infrastructure/IPlayfield.hpp"
#include "IO/Commands/CreateMap.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::features
{
    class CreateMapExecutor final
        : public core::ICommandExecutor<io::CreateMap>
    {
    public:
        CreateMapExecutor(
            IPlayfield& playfield,
            EventLog& eventLog,
            const std::uint32_t& tick
        );

        void execute(const io::CreateMap& command) override;

    private:
        IPlayfield& _playfield;
        EventLog& _eventLog;
        const std::uint32_t& _tick;
    };
}