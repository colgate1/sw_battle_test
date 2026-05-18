#pragma once

#include "Core/Components/IComponent.hpp"

namespace sw::features
{
	class ActionCompletedComponent final : public core::IComponent
	{
	public:
		bool isCompleted() const
		{
			return _completed;
		}

		void markCompleted()
		{
			_completed = true;
		}

		void reset()
		{
			_completed = false;
		}

	private:
		bool _completed = false;
	};
}