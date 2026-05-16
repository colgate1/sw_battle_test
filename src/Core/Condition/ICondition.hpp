#pragma once

namespace sw::core
{
    template <typename TContext>
    class ICondition
    {
    public:
        virtual ~ICondition() = default;

        virtual bool isSatisfied(const TContext& context) const = 0;
    };
}