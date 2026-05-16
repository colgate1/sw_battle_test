#pragma once

namespace sw::core
{
    template <typename TProcessContext>
    class IActionProcessor
    {
    public:
        virtual ~IActionProcessor() = default;

        virtual bool canProcess(
            const TProcessContext& context
        ) const = 0;

        virtual bool process(
            TProcessContext& context
        ) const = 0;
    };
}