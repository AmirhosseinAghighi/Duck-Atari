difLevel diffLevels[4][10] = {
        {
                {80, 7, 3000, 100, 1, 15000, 50, 2, 7000, 60, 2, 40, 4000},
                {40, 5, 3000, 100, 2, 13000, 60, 2, 7000, 60, 2, 50, 4000},
                {40, 5, 3000, 90, 3, 12000, 60, 3, 6000, 60, 2, 50, 3000},
                {70, 6, 2000, 80, 3, 11000, 40, 4, 6000, 60, 3, 60, 3000},
                {60, 6, 2000, 70, 3, 8000, 60, 4, 5000, 50, 3, 50, 3000},
                {60, 6, 2000, 60, 3, 8000, 80, 4, 4000, 50, 4, 40, 2000},
                {80, 8, 1000, 60, 4, 6000, 80, 4, 4000, 50, 4, 50, 2000},
                {80, 6, 1000, 60, 4, 6000, 90, 3, 3000, 60, 3, 40, 1000},
                {100, 4, 1000, 50, 3, 4000, 100, 2, 3000, 80, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000}
        },
        { // normal
                {60, 6, 2000, 70, 3, 8000, 60, 4, 5000, 50, 3, 50, 3000},
                {60, 6, 2000, 60, 3, 8000, 80, 4, 4000, 50, 4, 40, 2000},
                {80, 8, 1000, 60, 4, 6000, 80, 4, 4000, 50, 4, 50, 2000},
                {80, 6, 1000, 60, 4, 6000, 90, 3, 3000, 60, 3, 40, 1000},
                {100, 4, 1000, 50, 3, 4000, 100, 2, 3000, 80, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000}

        },

        {// hard
                {80, 6, 1000, 60, 4, 6000, 90, 3, 3000, 60, 3, 40, 1000},
                {100, 4, 1000, 50, 3, 4000, 100, 2, 3000, 80, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
                {100, 4, 800, 30, 3, 2000, 100, 3, 2000, 100, 2, 50, 1000},
        },

        { // mortal
                {100, 6, 800, 20, 3, 2000, 100, 3, 3000, 100, 2, 50, 1000},
                {100, 6, 800, 20, 3, 2000, 100, 3, 3000, 100, 2, 50, 1000},
                {100, 6, 800, 20, 3, 2000, 100, 3, 3000, 100, 2, 50, 1000},
                {100, 6, 800, 20, 3, 2000, 100, 3, 3000, 100, 2, 50, 1000},
                {100, 6, 800, 20, 3, 2000, 100, 3, 3000, 100, 2, 50, 1000},
                {100, 6, 800, 20, 3, 2000, 100, 3, 3000, 100, 2, 50, 1000},
                {100, 6, 800, 20, 3, 2000, 100, 3, 3000, 100, 2, 50, 1000},
                {100, 6, 800, 20, 3, 2000, 100, 3, 3000, 100, 2, 50, 1000},
                {100, 6, 800, 20, 3, 2000, 100, 3, 3000, 100, 2, 50, 1000},
                {100, 6, 800, 20, 3, 2000, 100, 3, 3000, 100, 2, 50, 1000}
        }
};




//mineSpawnCoolDown = 5000;
//
//cargoSpawnChance = easyLevels[currentDifficullityLevel].cargoSpawnChance;
//maxSpawnedCargo = easyLevels[currentDifficullityLevel].maxSpawnedCargo;
//cargoSpawnCooldown = 15000;
//
//bomberSpawnChance = easyLevels[currentDifficullityLevel].bomberSpawnChance;
//maxSpawnedBomber = easyLevels[currentDifficullityLevel].maxSpawnedBomber;
//bomberSpawnCoolDown = 7000;
//
//jetSpawnChance = easyLevels[currentDifficullityLevel].jetSpawnChance;
//maxSpawnedJet = easyLevels[currentDifficullityLevel].jetShootChance;
//jetShootChance = easyLevels[currentDifficullityLevel].jetShootChance;
//jetSpawnCooldown = 4000;

//mineSpawnChance = 50;
//maxSpawnedMines = 7;
//
//cargoSpawnChance = 20;
//maxSpawnedCargo = 1;
//
//bomberSpawnChance = 50;
//maxSpawnedBomber = 2;
//
//jetSpawnChance = 60;
//maxSpawnedJet = 2;
//jetShootChance = 40;
