#pragma once

#include "IO/System/CommandParser.hpp"
#include "IO/System/PrintDebug.hpp"

#include <functional>
#include <utility>
#include <vector>

namespace sw::core
{
    using DeferredCommands = std::vector<std::function<void()>>;

    template <typename TCommand, typename TExecutor>
    void addCommandCollector(
        sw::io::CommandParser& parser,
        TExecutor& executor,
        std::ostream& debugOut,
        DeferredCommands& deferredCommands)
    {
        parser.add<TCommand>(
            [&executor, &debugOut, &deferredCommands](TCommand command)
            {
                sw::printDebug(debugOut, command);

                deferredCommands.emplace_back(
                    [&executor, command = std::move(command)]()
                    {
                        executor.execute(command);
                    });
            });
    }
}