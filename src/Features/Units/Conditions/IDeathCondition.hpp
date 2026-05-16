#pragma once

#include "Features/Units/Infrastructure/IUnit.hpp"

namespace sw::features
{
    using IDeathCondition = core::ICondition<IUnit>;
}