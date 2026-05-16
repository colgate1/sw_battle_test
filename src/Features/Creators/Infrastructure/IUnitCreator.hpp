#pragma once

#include "Core/Creators/ICreator.hpp"
#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{
    template <typename TCreationData>
    using IUnitCreator = core::ICreator<IUnit, TCreationData>;
}