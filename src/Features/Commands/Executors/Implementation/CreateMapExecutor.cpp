#include "Features/Commands/Executors/Infrastructure/CreateMapExecutor.hpp"

#include "Features/Playfield/Data/PlayfieldSize.hpp"
#include "IO/Events/MapCreated.hpp"

namespace sw::features
{
    CreateMapExecutor::CreateMapExecutor(
        IPlayfield& playfield,
        EventLog& eventLog,
        const std::uint32_t& tick
    )
        : _playfield(playfield)
        , _eventLog(eventLog)
        , _tick(tick)
    {
    }

    void CreateMapExecutor::execute(const io::CreateMap& command)
    {
        _playfield.createMap(
            PlayfieldSize{
                command.width,
                command.height
            }
        );

        const PlayfieldSize size = _playfield.getMapSize();

        _eventLog.log(
            _tick,
            io::MapCreated{
                size.width,
                size.height
            }
        );
    }
}