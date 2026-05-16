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