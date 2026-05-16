#include "Features/BattleSimulation/Infrastructure/BattleSimulation.hpp"

#include "Features/Units/Infrastructure/IUnit.hpp"

#include <utility>

namespace sw::features
{
	BattleSimulation::BattleSimulation(
		IPlayfield& playfield,
		std::vector<std::unique_ptr<IBattleActionProcessor>> turnActiveProcessors,
		std::vector<std::unique_ptr<IBattleActionProcessor>> turnEndProcessors,
		std::uint32_t& tick) :
			_playfield(playfield),
			_turnActiveProcessors(std::move(turnActiveProcessors)),
			_turnEndProcessors(std::move(turnEndProcessors)),
			_tick(tick)
	{}

	void BattleSimulation::process()
	{
		while (!endSimulation())
		{
			const std::vector<std::uint32_t> aliveUnitIds = _playfield.getAliveUnitIds();

			if (aliveUnitIds.empty())
			{
				return;
			}

			for (std::uint32_t unitId : aliveUnitIds)
			{
				processTurn(unitId);
			}

			for (std::uint32_t unitId : aliveUnitIds)
			{
				processTurnEnd(unitId);
			}

			++_tick;
		}
	}

	void BattleSimulation::processTurn(std::uint32_t unitId)
	{
		IUnit& unit = _playfield.getUnit(unitId);
		BattleActionContext context{unitId, _playfield, _tick};

		for (const auto& processor : _turnActiveProcessors)
		{
			if (processor->process(context))
			{
				break;
			}
		}

		for (const auto& processor : _turnEndProcessors)
		{
			processor->process(context);
		}
	}

	void BattleSimulation::processTurnEnd(std::uint32_t unitId)
	{
		IUnit& unit = _playfield.getUnit(unitId);

		if (unit.isDead())
			return;

		BattleActionContext context{
			unitId,
			_playfield,
			_tick
		};
		for (const auto& processor : _turnEndProcessors)
			processor->process(context);
	}
	bool BattleSimulation::endSimulation() const
	{
		const std::vector<std::uint32_t> aliveUnitIds = _playfield.getAliveUnitIds();

		if (aliveUnitIds.size() <= 1)
		{
			return true;
		}

		for (std::uint32_t unitId : aliveUnitIds)
		{
				BattleActionContext context{unitId, _playfield, _tick};

				for (const auto& processor : _turnActiveProcessors)
				{
					if (processor->canProcess(context))
					{
						return false;
					}
				}
			}

			return true;
		}
	}
