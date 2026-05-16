#pragma once

namespace sw::core
{
    template <typename TCommand>
    class ICommandExecutor
    {
    public:
        virtual ~ICommandExecutor() = default;

        virtual void execute(const TCommand& command) = 0;
    };
}