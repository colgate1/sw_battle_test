#pragma once

#include <memory>

namespace sw::core
{
    template <typename TResult, typename TCreationData>
    class ICreator
    {
    public:
        virtual ~ICreator() = default;

        virtual std::unique_ptr<TResult> create(
            const TCreationData& data
        ) const = 0;
    };
}