#include "Core/Commands/Helpers/AddCommandCollector.hpp"
#include "Features/BattleSimulation/Infrastructure/BattleSimulation.hpp"
#include "Features/BattleSimulation/Processors/Infrastructure/ActionCompletedResetProcessor.hpp"
#include "Features/BattleSimulation/Processors/Infrastructure/DeathProcessor.hpp"
#include "Features/BattleSimulation/Processors/Infrastructure/MoveProcessor.hpp"
#include "Features/BattleSimulation/Processors/Infrastructure/SkillProcessor.hpp"
#include "Features/Commands/Executors/Infrastructure/CreateMapExecutor.hpp"
#include "Features/Commands/Executors/Infrastructure/MarchExecutor.hpp"
#include "Features/Commands/Executors/Infrastructure/SpawnHunterExecutor.hpp"
#include "Features/Commands/Executors/Infrastructure/SpawnTowerExecutor.hpp"
#include "Features/Commands/Executors/Infrastructure/SpawnSwordsmanExecutor.hpp"
#include "Features/Creators/Infrastructure/HunterCreator.hpp"
#include "Features/Creators/Infrastructure/TowerCreator.hpp"
#include "Features/Creators/Infrastructure/SwordsmanCreator.hpp"
#include "Features/Playfield/Infrastructure/Playfield.hpp"
#include "Features/Skills/Factories/Infrastructure/SkillFactory.hpp"

#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnTower.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
    using namespace sw;

    if (argc != 2) {
        throw std::runtime_error("Error: No file specified in command line argument");
    }

    std::ifstream file(argv[1]);
    if (!file) {
        throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
    }

    uint32_t tick = 1;
    EventLog eventLog;

    features::Playfield playfield;

    features::SkillFactory skillFactory;

    features::SwordsmanCreator swordsmanCreator(skillFactory);
    features::HunterCreator hunterCreator(skillFactory);
    features::TowerCreator towerCreator(skillFactory);

    features::CreateMapExecutor createMapExecutor(playfield, eventLog, tick);

    features::SpawnSwordsmanExecutor spawnSwordsmanExecutor(
        playfield,
        swordsmanCreator,
        eventLog,
        tick
    );

    features::SpawnHunterExecutor spawnHunterExecutor(
        playfield,
        hunterCreator,
        eventLog,
        tick
    );

    features::SpawnTowerExecutor spawnTowerExecutor(
        playfield,
        towerCreator,
        eventLog,
        tick
    );

    features::MarchExecutor marchExecutor(playfield, eventLog,
                                          tick);

    core::DeferredCommands deferredCommands;

    std::cout << "Commands:\n";

    io::CommandParser parser;
    addCommandCollector<io::CreateMap>(
        parser,
        createMapExecutor,
        std::cout,
        deferredCommands
    );

    addCommandCollector<io::SpawnSwordsman>(
        parser,
        spawnSwordsmanExecutor,
        std::cout,
        deferredCommands
    );

    addCommandCollector<io::SpawnHunter>(
        parser,
        spawnHunterExecutor,
        std::cout,
        deferredCommands
    );

    addCommandCollector<io::SpawnTower>(
        parser,
        spawnTowerExecutor,
        std::cout,
        deferredCommands
    );

    addCommandCollector<io::March>(
        parser,
        marchExecutor,
        std::cout,
        deferredCommands
    );

    parser.parse(file);

    std::cout << "\n\nEvents:\n";

    for (auto &deferredCommand: deferredCommands) {
        deferredCommand();
    }
    std::vector<std::unique_ptr<features::IBattleActionProcessor> > turnActiveProcessors;
    std::vector<std::unique_ptr<features::IBattleActionProcessor> > turnEndedProcessors;
    std::vector<std::unique_ptr<features::IBattleActionProcessor> > roundCompleteProcessors;

    turnActiveProcessors.push_back(std::make_unique<features::SkillProcessor>(eventLog));
    turnActiveProcessors.push_back(std::make_unique<features::MoveProcessor>(eventLog));
    turnEndedProcessors.push_back(std::make_unique<features::DeathProcessor>(eventLog));
	roundCompleteProcessors.push_back(std::make_unique<features::ActionCompletedResetProcessor >(eventLog));
    features::BattleSimulation battleSimulation(
        playfield,
        std::move(turnActiveProcessors),
        std::move(turnEndedProcessors),
        std::move(roundCompleteProcessors),
        tick
    );

    battleSimulation.process();

    return 0;
}
