# Goal

The goal of this assignment is to demonstrate software design skills.

Do not worry about performance, multithreading, or integrating external libraries.
We do not expect deterministic simulation results, as that would only make the task more complicated.

There is no strict time limit, but the expected completion time is no more than 6–8 hours.

What we would like to see:

Clear and well-structured code with transparent logic.

A clear separation of responsibilities between project entities.

An extensible architecture that makes it easy to add new entities and interaction mechanics.

Imagine that after you, 10 junior developers will join the project and will be adding new features at the same time.

Please read the README.MD files in the Core and Feature directories. They will help you better understand the goals of the assignment.

Please also leave notes in the KNOWN_ISSUES.md document, describing any known shortcomings or doubts about your solution, for example due to lack of time.

# Task

Create a turn-based simulation of combat encounters between units on a map for testing game mechanics.

Units can be placed on a map of size W×H cells.

Units differ by type, actions, and attributes.

Each unit has a unique identifier, Id, which is an integer.

During one turn, each unit may perform one action.

Units perform their actions in the order in which they were created.

A unit is always placed at some coordinates on the map.

A unit may occupy a cell, preventing other units from standing on it.

Most units have an HP attribute, which stands for Health Points.

If a unit’s HP is less than or equal to 0, the unit still performs its actions during the current turn and disappears before the beginning of the next turn.

Some units have the ability to move:

They can move to any of the eight adjacent cells during one turn.

If the target cannot be reached in one turn, they continue moving toward it during subsequent turns.

Static units must remain stationary under all circumstances.

The simulation ends when there are no units capable of acting on the next turn, or when only one unit remains on the map.

# Units to Implement

## Swordsman

Attributes: HP, Strength

Actions:

Crushing Blow: attacks one random unit in an adjacent cell, dealing Strength damage.

If there is no one to attack, the unit moves.

## Hunter

Attributes: HP, Agility, Strength, Range

Actions:

Quick Shot: shoots one random unit at a distance from 2 to Range cells, dealing Agility damage. The Hunter can shoot only if there are no other units in adjacent cells.

Shadow Strike: if the Hunter cannot shoot, it attacks one random unit in an adjacent cell, dealing Strength damage.

If there is no one to attack, the unit moves.

# Application

When launched, the application receives a path to a simulation scenario file. The file contains commands for creating the map and units, as well as commands for moving units across the map.

The application must output all occurring events to stdout.

Since there are no obstacles on the map, complex pathfinding algorithms are not required.

# Commands

CREATE_MAP W H — Creates a map of size W×H. This command starts every scenario.

SPAWN_SWORDSMAN I X Y H S — Creates a Swordsman with identifier I at position X,Y, with health H and strength S.

SPAWN_HUNTER I X Y H A S R — Creates a Hunter with identifier I at position X,Y, with health H, agility A, strength S, and range R.

MARCH I X Y — Orders unit I to move to position X,Y.

# Events

MAP_CREATED — Map creation.

MARCH_STARTED, MARCH_ENDED — Start and end of a unit’s movement.

UNIT_SPAWNED, UNIT_DIED — Unit creation and death.

UNIT_MOVED — A unit moves to another cell.

UNIT_ATTACKED — One unit attacks another unit.

The command parser and event logging code are already included in the project. You may change them if necessary. The input and output formats must not be changed.

An example scenario can be found in the commands_example.txt file.
An example event log can be found in the main.cpp file.

# Restrictions

Do not add any external third-party dependencies. Use only the standard library.

You may change the project in any way required to achieve the goal, even if that means not using the provided structure and code.

This is neither a plus nor a minus. We provided the structure and code to simplify the task and save you time.

# Technical Requirements

OS: Ubuntu

Compiler: clang 15+

Standard: C++17 or newer

Build system: CMake. The project must contain a CMakeLists.txt file.

The assignment must be published in any public Git repository, such as GitHub, Bitbucket, and so on.

During the assignment, you may send any questions.

# Planned Extensions

When designing the solution, please take into account the planned addition of new units, actions, and attributes.

The ability to create such units with such behavior without modifying the Core code is an important evaluation criterion.

This functionality does not need to be implemented in code. It is only a hint regarding extensibility.

## Tower

Attributes: HP, Power

Actions:

Aimed Shot: shoots one random unit at a distance from 2 to 5 cells, dealing Power damage.

Cannot move.

## Healer

Attributes: HP, Spirit

Actions:

Minor Heal: restores Spirit health points to one random unit within a radius of 2 cells.

If there is no one to heal, the unit moves.

## Raven

Attributes: HP, Agility

Flying unit:

Does not occupy a cell on the map.

Can move 2 cells per turn.

Cannot be attacked in melee combat.

Can be attacked by ranged combat, but the minimum and maximum attack distance of the shooter against the Raven are reduced by 1.

Actions:

Claw Strike: attacks one random unit in adjacent cells, dealing Agility damage.

If there is no one to attack, the unit moves.

## Mine

Attributes: Power

Cannot be attacked.

Does not occupy a cell on the map.

Actions:

If there is a unit within a radius of 2 cells, the Mine explodes on the next turn, dealing Power damage to all units within a radius of 3 cells.

After exploding, it disappears.

Cannot move.

Result

==================
## Commands

```text
CREATE_MAP width=10 height=10
SPAWN_SWORDSMAN unitId=1 x=0 y=0 hp=5 strength=2
SPAWN_HUNTER unitId=2 x=9 y=0 hp=10 agility=5 strength=1 range=4
MARCH unitId=1 targetX=9 targetY=0
MARCH unitId=2 targetX=0 targetY=0
SPAWN_SWORDSMAN unitId=3 x=0 y=9 hp=10 strength=2
MARCH unitId=3 targetX=0 targetY=0
```

## Events

```text
[1] MAP_CREATED width=10 height=10 
[1] UNIT_SPAWNED unitId=1 unitType=SPAWN_SWORDSMAN x=0 y=0 
[1] UNIT_SPAWNED unitId=2 unitType=SPAWN_HUNTER x=9 y=0 
[1] MARCH_STARTED unitId=1 x=0 y=0 targetX=9 targetY=0 
[1] MARCH_STARTED unitId=2 x=9 y=0 targetX=0 targetY=0 
[1] UNIT_SPAWNED unitId=3 unitType=SPAWN_SWORDSMAN x=0 y=9 
[1] MARCH_STARTED unitId=3 x=0 y=9 targetX=0 targetY=0 
[1] UNIT_MOVED unitId=1 x=1 y=0 
[1] UNIT_MOVED unitId=2 x=8 y=0 
[1] UNIT_MOVED unitId=3 x=0 y=8 
[2] UNIT_MOVED unitId=1 x=2 y=0 
[2] UNIT_MOVED unitId=2 x=7 y=0 
[2] UNIT_MOVED unitId=3 x=0 y=7 
[3] UNIT_MOVED unitId=1 x=3 y=0 
[3] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=5 targetHp=0 
[3] UNIT_DIED unitId=1 
[3] UNIT_MOVED unitId=3 x=0 y=6 
[4] UNIT_MOVED unitId=2 x=6 y=0 
[4] UNIT_MOVED unitId=3 x=0 y=5 
[5] UNIT_MOVED unitId=2 x=5 y=0 
[5] UNIT_MOVED unitId=3 x=0 y=4 
[6] UNIT_MOVED unitId=2 x=4 y=0 
[6] UNIT_MOVED unitId=3 x=0 y=3 
[7] UNIT_ATTACKED attackerUnitId=2 targetUnitId=3 damage=5 targetHp=5 
[7] UNIT_MOVED unitId=3 x=0 y=2 
[8] UNIT_ATTACKED attackerUnitId=2 targetUnitId=3 damage=5 targetHp=0 
[8] UNIT_MOVED unitId=3 x=0 y=1 
[8] UNIT_DIED unitId=3 
```
