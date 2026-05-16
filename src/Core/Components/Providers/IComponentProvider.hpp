#pragma once

#include <typeindex>

#include "Core/Components/IComponent.hpp"

namespace sw::core
{
    class IComponentProvider
    {
    public:
        virtual ~IComponentProvider() = default;

        virtual IComponent* findComponent(std::type_index type) = 0;
        virtual const IComponent* findComponent(std::type_index type) const = 0;
    };
}