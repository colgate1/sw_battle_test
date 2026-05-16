#pragma once

#include <typeindex>
#include <type_traits>

#include "Core/Components/IComponent.hpp"
#include "Core/Components/Providers/IComponentProvider.hpp"

namespace sw::core
{
    template <typename TComponent>
    TComponent* findComponent(IComponentProvider& provider)
    {
        using Component = std::remove_cv_t<TComponent>;

        static_assert(
            std::is_base_of_v<IComponent, Component>,
            "TComponent must derive from sw::core::IComponent"
        );

        IComponent* component = provider.findComponent(
            std::type_index(typeid(Component))
        );

        if (component == nullptr)
            return nullptr;

        return static_cast<TComponent*>(component);
    }

    template <typename TComponent>
    const TComponent* findComponent(const IComponentProvider& provider)
    {
        using Component = std::remove_cv_t<TComponent>;

        static_assert(
            std::is_base_of_v<IComponent, Component>,
            "TComponent must derive from sw::core::IComponent"
        );

        const IComponent* component = provider.findComponent(
            std::type_index(typeid(Component))
        );

        if (component == nullptr)
            return nullptr;

        return static_cast<const TComponent*>(component);
    }
}