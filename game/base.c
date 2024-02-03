extern int Score;
#include "Diff.c"
#include "math.c"
#include "collision.c"
#include "debug.c"
#include "bullets.c"
#include "explosions.c"
#include "rewards.c"
#include "mines.c"
#include "cargoSpaceShips.c"
#include "bomber.c"
#include "jets.c"

extern int GameStatus;
int elementsOnScreen = 0;
int maximumElements = 10;
int scrollSpeed = 1;
spaceShip *mainSpaceShip = NULL;
texture *fuelBarTexture = NULL;
texture *fuelProgressBarRedTexture = NULL;
texture *fuelProgressBarOrangeTexture = NULL;
texture *fuelProgressBarGreenTexture = NULL;
texture *HeartTexture = NULL;
texture *specialAmmoTexture = NULL;
texture *mineTexture[2] = {NULL}; // will be load in first usage.
texture *cargoSpaceShipTexture = NULL;
Uint32 gameStartTimer = 0;
Uint32 gameDiffLevelChangedTime = 0;
int currentDifficullityLevel = 0;
int Score = 0;
Uint32 powerBulletActive = 0;
Uint32 lastScoreChange = 0;

void newGame() {
    mainSpaceShip = (spaceShip *)malloc(sizeof(spaceShip));
    mainSpaceShip -> texture = loadTexture("../images/Game/spaceShip.png");
    mainSpaceShip -> backfire1Texture = loadTexture("../images/Game/Backfire1.png");
    mainSpaceShip -> backfire2Texture = loadTexture("../images/Game/Backfire2.png");
    mainSpaceShip -> backfire3Texture = loadTexture("../images/Game/Backfire3.png");
    mainSpaceShip -> bulletTexture = loadTexture("../images/Game/bullet.png");
    mainSpaceShip -> powerModeTexture = loadTexture("../images/Game/spaceShip-power.png");
    mainSpaceShip -> shieldModeTexture = loadTexture("../images/Game/spaceShip-shield.png");
    mainSpaceShip -> sheildTimer = 0;
    mainSpaceShip -> specialAmmoAmount = 2;
    powerBulletActive = 0;
    mainSpaceShip -> coords.w = mainSpaceShip -> texture -> width / 4;
    mainSpaceShip -> coords.h = mainSpaceShip -> texture -> height / 4;
    mainSpaceShip -> coords.x = -mainSpaceShip -> coords.w;
    mainSpaceShip -> coords.y = Height / 2;
    mainSpaceShip -> Vspeed = 4;
    mainSpaceShip -> Hspeed = Height / 100;
    mainSpaceShip -> fuel = 1000;
    if (selectedDiffLevel == mortal) {
        mainSpaceShip -> health = 1;
    } else {
        mainSpaceShip -> health = 5;
    }
    mainSpaceShip -> shakeFrame = -1;
    mainSpaceShip -> maxShakeFrame = 0;

    mainSpaceShip -> collision[0].x = 25;
    mainSpaceShip -> collision[0].y = 0;
    mainSpaceShip -> collision[0].w = 32;
    mainSpaceShip -> collision[0].h = 53;

    mainSpaceShip -> collision[1].x = 58;
    mainSpaceShip -> collision[1].y = 18;
    mainSpaceShip -> collision[1].w = 15;
    mainSpaceShip -> collision[1].h = 35;

    mainSpaceShip -> collision[2].x = 73;
    mainSpaceShip -> collision[2].y = 33;
    mainSpaceShip -> collision[2].w = 19;
    mainSpaceShip -> collision[2].h = 20;

    mainSpaceShip -> collision[3].x = 0;
    mainSpaceShip -> collision[3].y = 53;
    mainSpaceShip -> collision[3].w = 146;
    mainSpaceShip -> collision[3].h = 48;

    mainSpaceShip -> collision[4].x = 25;
    mainSpaceShip -> collision[4].y = 96;
    mainSpaceShip -> collision[4].w = 32;
    mainSpaceShip -> collision[4].h = 53;

    mainSpaceShip -> collision[5].x = 58;
    mainSpaceShip -> collision[5].y = 94;
    mainSpaceShip -> collision[5].w = 15;
    mainSpaceShip -> collision[5].h = 35;

    mainSpaceShip -> collision[6].x = 73;
    mainSpaceShip -> collision[6].y = 101;
    mainSpaceShip -> collision[6].w = 19;
    mainSpaceShip -> collision[6].h = 20;
    // we should make this later ...
    // we should init every texture here and free them after the game finished.

    //loading screen ui textures
    fuelBarTexture = loadTexture("../images/Game/fuel-bar.png");
    fuelProgressBarRedTexture = loadTexture("../images/Game/fuel-progressbar.png");
    fuelProgressBarOrangeTexture = loadTexture("../images/Game/fuel-progressbar-o.png");
    fuelProgressBarGreenTexture = loadTexture("../images/Game/fuel-progressbar-g.png");
    HeartTexture = loadTexture("../images/Game/heart.png");
    specialAmmoTexture = loadTexture("../images/Game/special-ammo.png");
    bulletTexturesByTypes[0] = loadTexture("../images/Game/bullet.png");
    bulletTexturesByTypes[1] = loadTexture("../images/Game/bomb.png");
    bulletTexturesByTypes[2] = loadTexture("../images/Game/jet-bullet.png");
    bulletTexturesByTypes[3] = loadTexture("../images/Game/bullet-power.png");
    rewardsTextureByType[0] = loadTexture("../images/Game/jerrycan.png");
    rewardsTextureByType[1] = HeartTexture;
    rewardsTextureByType[2] = loadTexture("../images/Game/shield.png");;
    rewardsTextureByType[3] = loadTexture("../images/Game/specialAmmoBox.png");
    bomberTexture = loadTexture("../images/Game/bomber.png");
//    bomberBombTexture = loadTexture("../images/Game/bomb.png");
    jetTexture = loadTexture("../images/Game/jet.png");
    loadExplosionsTextures();

    gameStartTimer = SDL_GetTicks();
    gameDiffLevelChangedTime = gameStartTimer;

    lastMineSpawnTime = gameStartTimer;
    mineSpawnChance = diffLevels[selectedDiffLevel][0].mineSpawnChance;
    maxSpawnedMines = diffLevels[selectedDiffLevel][0].maxSpawnedMines;
    mineSpawnCoolDown = diffLevels[selectedDiffLevel][0].mineSpawnCoolDown;

    lastCargoSpawnTime = gameStartTimer;
    cargoSpawnChance = diffLevels[selectedDiffLevel][0].cargoSpawnChance;
    maxSpawnedCargo = diffLevels[selectedDiffLevel][0].maxSpawnedCargo;
    cargoSpawnCooldown = diffLevels[selectedDiffLevel][0].cargoSpawnCooldown;

    lastBomberSpawnTime = gameStartTimer + 20000;
//    lastBomberSpawnTime = gameStartTimer;
    bomberSpawnChance = diffLevels[selectedDiffLevel][0].bomberSpawnChance;
    maxSpawnedBomber = diffLevels[selectedDiffLevel][0].maxSpawnedBomber;
    bomberSpawnCoolDown = diffLevels[selectedDiffLevel][0].bomberSpawnCoolDown;

    lastJetSpawnTime = gameStartTimer + 30000;
//    lastJetSpawnTime = gameStartTimer;
    jetSpawnChance = diffLevels[selectedDiffLevel][0].jetSpawnChance;
    maxSpawnedJet = diffLevels[selectedDiffLevel][0].maxSpawnedJet;
    jetShootChance = diffLevels[selectedDiffLevel][0].jetShootChance;
    jetSpawnCooldown = diffLevels[selectedDiffLevel][0].jetSpawnCooldown;
    currentDifficullityLevel = 0;
    scrollSpeed = 1;
    Score = 0;

    stopMusic();
    playGameMusic();
}


void updateDifficullityLevel() {
    if (currentDifficullityLevel == 9)
        return;


    if (SDL_GetTicks() - gameDiffLevelChangedTime >= 90000) {
        currentDifficullityLevel++;
        gameDiffLevelChangedTime = SDL_GetTicks();
    } else {
        return;
    }

//    if (scrollSpeed == 5) {
//        stopMusic();
//        playHighSpeedGameMusic();
//    }

    if (scrollSpeed >= 5) {
        mainSpaceShip -> Vspeed = Width / 50;
        mainSpaceShip -> Hspeed = Height / 50;
    }

    mineSpawnChance = diffLevels[selectedDiffLevel][currentDifficullityLevel].mineSpawnChance;
    maxSpawnedMines = diffLevels[selectedDiffLevel][currentDifficullityLevel].maxSpawnedMines;
    mineSpawnCoolDown = diffLevels[selectedDiffLevel][currentDifficullityLevel].mineSpawnCoolDown;

    cargoSpawnChance = diffLevels[selectedDiffLevel][currentDifficullityLevel].cargoSpawnChance;
    maxSpawnedCargo = diffLevels[selectedDiffLevel][currentDifficullityLevel].maxSpawnedCargo;
    cargoSpawnCooldown = diffLevels[selectedDiffLevel][currentDifficullityLevel].cargoSpawnCooldown;

    bomberSpawnChance = diffLevels[selectedDiffLevel][currentDifficullityLevel].bomberSpawnChance;
    maxSpawnedBomber = diffLevels[selectedDiffLevel][currentDifficullityLevel].maxSpawnedBomber;
    bomberSpawnCoolDown = diffLevels[selectedDiffLevel][currentDifficullityLevel].bomberSpawnCoolDown;

    jetSpawnChance = diffLevels[selectedDiffLevel][currentDifficullityLevel].jetSpawnChance;
    maxSpawnedJet = diffLevels[selectedDiffLevel][currentDifficullityLevel].maxSpawnedJet;
    jetShootChance = diffLevels[selectedDiffLevel][currentDifficullityLevel].jetShootChance;
    jetSpawnCooldown = diffLevels[selectedDiffLevel][currentDifficullityLevel].jetSpawnCooldown;

    scrollSpeed = currentDifficullityLevel + 1;
}

void shakeSpaceShip(int max) {
    if (mainSpaceShip -> shakeFrame == -1) {
        mainSpaceShip -> shakeFrame = 0;
        mainSpaceShip -> maxShakeFrame = max;
        mainSpaceShip -> shakeChange = 2;
    }
}

int haveEnoughFuel(int amount);
void renderCorruptedBackfire();
void renderBackfire() {
    if (!haveEnoughFuel(200)) {
        renderCorruptedBackfire();
        return;
    }
    static int backfireType = 0;
    backfireType++;
    int x = mainSpaceShip -> coords.x - (mainSpaceShip -> backfire1Texture -> width / 4);
    int y = mainSpaceShip -> coords.y + (mainSpaceShip -> coords.h / 2) - (mainSpaceShip -> backfire1Texture -> height / 8);
//    SDL_Log("wtf %d:%d | %d:%d", mainSpaceShip -> coords.x, x, mainSpaceShip -> coords.y, y);
    SDL_Rect pos = {x, y, mainSpaceShip -> backfire1Texture -> width / 4, mainSpaceShip -> backfire1Texture -> height / 4};
    if (backfireType < 60) {
        SDL_RenderCopy(Render, mainSpaceShip -> backfire1Texture -> texture, NULL, &pos);
    } else if (backfireType < 120) {
        SDL_RenderCopy(Render, mainSpaceShip -> backfire2Texture -> texture, NULL, &pos);
    } else if (backfireType <= 180) {
        SDL_RenderCopy(Render, mainSpaceShip -> backfire3Texture -> texture, NULL, &pos);
    }

    if (backfireType == 180)
        backfireType = 0;
}

void renderCorruptedBackfire() {
    static int backfireType = 0;
    backfireType++;
//    if (randomNumber(1, 100) >= 60) {
//        SDL_Delay(randomNumber(10, 150));
//        return;
//    }
    int x = mainSpaceShip -> coords.x - (mainSpaceShip -> backfire1Texture -> width / 4);
    int y = mainSpaceShip -> coords.y + (mainSpaceShip -> coords.h / 2) - (mainSpaceShip -> backfire1Texture -> height / 8);
    SDL_Rect pos = {x, y, mainSpaceShip -> backfire1Texture -> width / 4, mainSpaceShip -> backfire1Texture -> height / 4};
    if (backfireType < 30 && randomNumber(1, 100) > 40) {
        SDL_RenderCopy(Render, mainSpaceShip -> backfire1Texture -> texture, NULL, &pos);
    } else if ( backfireType >= 50 && backfireType < 80 && randomNumber(1, 100) > 20) {
        SDL_RenderCopy(Render, mainSpaceShip -> backfire2Texture -> texture, NULL, &pos);
    } else if (backfireType >= 100 && backfireType <= 120 && randomNumber(1, 100) > 60) {
        SDL_RenderCopy(Render, mainSpaceShip -> backfire3Texture -> texture, NULL, &pos);
    }

    if (backfireType == 120)
        backfireType = 0;
}

int preGameState = 0;
void renderPreGame() {
    SDL_Log("pre Game Running preState: %d  x: %d  y: %d", preGameState, mainSpaceShip -> coords.x, mainSpaceShip -> coords.y);
    SDL_RenderCopy(Render, mainSpaceShip -> texture -> texture, NULL, &(mainSpaceShip -> coords));
    //i will put this if to avoid over head of old calculation when we don't need it !
    if (preGameState >= 1 && preGameState <= 120) {
        renderCorruptedBackfire();
        preGameState++;
        return; // returning to avoid ...
    } else if (preGameState > 60) {
        mainSpaceShip -> Vspeed = Width / 100;
        preGameState = -1;
        GameStatus = Game;
    }else {
        renderBackfire();
    }
    if (mainSpaceShip -> coords.x > (mainSpaceShip -> backfire1Texture -> width / 4)) {
        preGameState++;
    } else {
        mainSpaceShip -> coords.x += mainSpaceShip -> Vspeed;
    }
}

void drawFuelBar() {
    double fuelPercentage = (mainSpaceShip -> fuel / 1000);
    SDL_Rect pos = {Width - fuelBarTexture -> width - 10, Height - 10 - fuelBarTexture -> height, fuelBarTexture -> width * fuelPercentage, fuelBarTexture -> height};
    if (fuelPercentage < 0.2){
        pos.x += 5;
        SDL_RenderCopy(Render, fuelProgressBarRedTexture -> texture, NULL, &pos);
        pos.x -= 5;
    } else if (fuelPercentage < 0.5) {
        SDL_RenderCopy(Render, fuelProgressBarOrangeTexture -> texture, NULL, &pos);
    } else {
        SDL_RenderCopy(Render, fuelProgressBarGreenTexture -> texture, NULL, &pos);
    }

    pos.w = fuelBarTexture -> width;
    SDL_RenderCopy(Render, fuelBarTexture -> texture, NULL, &pos);
}

void costFuel(int amount) {
    if (mainSpaceShip -> fuel - amount <= 0)
        mainSpaceShip -> fuel = 0;
    else
        mainSpaceShip -> fuel -= amount;
}

int haveEnoughFuel(int amount) {
    return amount <= mainSpaceShip -> fuel;
}

void drawHealth() {
    SDL_Rect pos = {Width - (mainSpaceShip -> health * (HeartTexture -> width + 10)), 10, HeartTexture -> width, HeartTexture -> height};
    for (int i = 0; i < mainSpaceShip -> health; ++i) {
        SDL_RenderCopy(Render, HeartTexture -> texture, NULL, &pos);
        pos.x += HeartTexture -> width + 10;
    }
}

void drawSpecialAmmo() {
    SDL_Rect pos = {10, Height - specialAmmoTexture -> height - 10, specialAmmoTexture -> height, specialAmmoTexture -> width};
    for (int i = 0; i < mainSpaceShip -> specialAmmoAmount; ++i) {
        SDL_RenderCopy(Render, specialAmmoTexture -> texture, NULL, &pos);
        pos.x += specialAmmoTexture -> width + 10;
    }
}

void giveSpecialAmoo() {
    if (mainSpaceShip -> specialAmmoAmount < 3) {
        mainSpaceShip -> specialAmmoAmount++;
    }
}

void giveShield() {
    Uint32 remainingSheild = mainSpaceShip -> sheildTimer;
    mainSpaceShip -> sheildTimer = SDL_GetTicks() + 10000;
    if (remainingSheild > SDL_GetTicks()) {
        mainSpaceShip -> sheildTimer += remainingSheild - SDL_GetTicks();
    }
}

void updateScore() {
    if (SDL_GetTicks() >= 500) {
        if (scrollSpeed > 4) {
            Score += 4;
        } else {
            Score += scrollSpeed;
        }
        lastScoreChange = SDL_GetTicks();
    }
}

void drawScore() {
    char string[6];
    Uint32 newScore = Score;
    if (newScore > 999999) {
        newScore = 999999;
    }
    sprintf(string, "%06d", newScore);
    SDL_Color scoreColor = {255, 255, 255};
    SDL_Texture *textTexture = loadFromRenderedText(string, scoreColor);
    SDL_Rect pos = {0, 0, 150, 60};
    SDL_RenderCopy(Render, textTexture, NULL, &(pos));
    SDL_DestroyTexture(textTexture);
}

bullet *checkSpaceShipCollisionWithBullets(SDL_Rect *data) {
    for (int i = 0; i < 7; ++i) {
        SDL_Rect *collision = &(mainSpaceShip -> collision[i]);
        SDL_Rect collisionRect = { data -> x + collision -> x, data -> y + collision -> y, collision -> w, collision -> h };
        bullet *result = checkBulletCollisionExcept(&collisionRect, 0);
        if (result != NULL)
            return result;
    }
    return NULL;
}

void renderOnePlayerGame() {
    Uint32 remainingSheild = mainSpaceShip -> sheildTimer;
    if (powerBulletActive != 0 && SDL_GetTicks() - powerBulletActive > 500)
        SDL_RenderCopy(Render, mainSpaceShip -> powerModeTexture -> texture, NULL, &(mainSpaceShip -> coords));
    else if (remainingSheild > SDL_GetTicks())
        SDL_RenderCopy(Render, mainSpaceShip -> shieldModeTexture -> texture, NULL, &(mainSpaceShip -> coords));
    else
        SDL_RenderCopy(Render, mainSpaceShip -> texture -> texture, NULL, &(mainSpaceShip -> coords));


    bullet *result = checkSpaceShipCollisionWithBullets(&(mainSpaceShip -> coords));
    if (result != NULL) {
        createExplosion(result -> data.x, result -> data.y);
        result -> deleted = 1;
        if (result -> type == 1) {
            damageSpaceShip(1);
            brokeEngineForATime(200);
            shakeSpaceShip(20);
        }

        if (result -> type == 2) {
            damageSpaceShip(1);
            brokeEngineForATime(200);
            shakeSpaceShip(30);
        }
    }

    if (mainSpaceShip -> shakeFrame >= 0) {
        if (mainSpaceShip -> shakeFrame < mainSpaceShip -> maxShakeFrame / 4) {
            mainSpaceShip -> coords.y += mainSpaceShip -> shakeChange;
            mainSpaceShip -> coords.x -= mainSpaceShip -> shakeChange;
            mainSpaceShip -> shakeFrame++;
        } else if (mainSpaceShip -> shakeFrame < mainSpaceShip -> maxShakeFrame / 2) {
            mainSpaceShip -> coords.x += mainSpaceShip -> shakeChange;
            mainSpaceShip -> coords.y -= mainSpaceShip -> shakeChange;
            mainSpaceShip -> shakeFrame++;
        } else if (mainSpaceShip -> shakeFrame < 3 * mainSpaceShip -> maxShakeFrame / 4) {
            mainSpaceShip -> coords.x += mainSpaceShip -> shakeChange;
            mainSpaceShip -> coords.y -= mainSpaceShip -> shakeChange;
            mainSpaceShip -> shakeFrame++;
        } else if (mainSpaceShip -> shakeFrame < mainSpaceShip -> maxShakeFrame) {
            mainSpaceShip -> coords.x -= mainSpaceShip -> shakeChange;
            mainSpaceShip -> coords.y += mainSpaceShip -> shakeChange;
            mainSpaceShip -> shakeFrame++;
        } else {
            mainSpaceShip -> shakeFrame = -1;
            mainSpaceShip -> maxShakeFrame = 0;
            mainSpaceShip -> shakeChange = 0;
        }
    }

    #if debug
        SDL_Log("Start drawing mines");
    #endif
    drawMines();
    #if debug
        SDL_Log("Start drawing cargos");
    #endif
    drawCargoSpaceShips();
    #if debug
        SDL_Log("Start drawing explosions");
    #endif
    renderBombers();
    renderJets();
    drawExplosions();
    renderBullets();
    renderRewards();

    // ui
    drawFuelBar();
    drawHealth();
    drawSpecialAmmo();

    //score
    updateScore();
    drawScore();

    if (debug) {
        drawCollisions();
    }

    updateDifficullityLevel();
}

void renderGameoverGame() {
    renderBombersWithoutMove();
    renderCargosWithoutMove();
    renderJetsWithoutMove();
    renderMinesWithoutMove();
    drawExplosions();
}

Uint32 brokenEngineTime = 0;
int brokenEngineTimer = 0;
void brokeEngineForATime(int time /*in ms*/) {
    brokenEngineTime = SDL_GetTicks();
    brokenEngineTimer = time;
}

void fixEngine() {
    brokenEngineTime = 0;
    brokenEngineTimer = 0;
}

extern void gameOver();
void damageSpaceShip(int amount) {
    if (mainSpaceShip -> sheildTimer > SDL_GetTicks())
        return;
    if (mainSpaceShip -> health > 0)
        mainSpaceShip -> health -= amount;

    if (mainSpaceShip -> health == 0) {
        gameOver();
    }
}

int checkCollision(SDL_Rect *data) {
    for (int i = 0; i < 7; ++i) {
        if ( ((data -> y + data -> h <= mainSpaceShip -> coords.y + mainSpaceShip -> collision[i].y) || (data -> y >= mainSpaceShip -> coords.y + mainSpaceShip -> collision[i].y + mainSpaceShip -> collision[i].h) || (data -> x + data -> w <= mainSpaceShip -> coords.x + mainSpaceShip -> collision[i].x) || (data -> x >= mainSpaceShip -> coords.x + mainSpaceShip -> collision[i].x + mainSpaceShip -> collision[i].w)) == 0 )
            return 1;
    }
    return 0;
}

void clearScreen() {
    clearMines();
    clearCargos();
    clearBombers();
    clearJets();
}

void gameOverDone() {
    deleteTexture(mainSpaceShip -> texture);
    mainSpaceShip -> texture = NULL;
    deleteTexture(mainSpaceShip -> backfire1Texture);
    mainSpaceShip -> backfire1Texture = NULL;
    deleteTexture(mainSpaceShip -> backfire2Texture);
    mainSpaceShip -> backfire2Texture = NULL;
    deleteTexture(mainSpaceShip -> backfire3Texture);
    mainSpaceShip -> backfire3Texture = NULL;
    deleteTexture(mainSpaceShip -> bulletTexture);
    mainSpaceShip -> bulletTexture = NULL;
    deleteTexture(mainSpaceShip -> powerModeTexture);
    mainSpaceShip -> powerModeTexture = NULL;
    deleteTexture(mainSpaceShip -> shieldModeTexture);
    mainSpaceShip -> shieldModeTexture = NULL;
    deleteTexture(fuelBarTexture);
    fuelProgressBarRedTexture = NULL;
    deleteTexture(fuelProgressBarRedTexture);
    fuelProgressBarRedTexture = NULL;
    deleteTexture(fuelProgressBarOrangeTexture);
    fuelProgressBarOrangeTexture = NULL;
    deleteTexture(fuelProgressBarGreenTexture);
    fuelProgressBarGreenTexture = NULL;
    deleteTexture(HeartTexture);
    HeartTexture = NULL;
    deleteTexture(specialAmmoTexture);
    specialAmmoTexture = NULL;
    deleteTexture(bulletTexturesByTypes[0]);
    bulletTexturesByTypes[0] = NULL;
    deleteTexture(bulletTexturesByTypes[1]);
    bulletTexturesByTypes[1] = NULL;
    deleteTexture(bulletTexturesByTypes[2]);
    bulletTexturesByTypes[2] = NULL;
    deleteTexture(bulletTexturesByTypes[3]);
    bulletTexturesByTypes[3] = NULL;
    deleteTexture(rewardsTextureByType[0]);
    rewardsTextureByType[0] = NULL;
    deleteTexture(rewardsTextureByType[1]);
    rewardsTextureByType[1] = NULL;
    deleteTexture(rewardsTextureByType[2]);
    rewardsTextureByType[2] = NULL;
    deleteTexture(rewardsTextureByType[3]);
    rewardsTextureByType[3] = NULL;
    deleteTexture(bomberTexture);
    bomberTexture = NULL;
    deleteTexture(jetTexture);
    jetTexture = NULL;
    if (cargoSpaceShipTexture != NULL) {
        deleteTexture(cargoSpaceShipTexture);
        cargoSpaceShipTexture = NULL;
    }

    if (mineTexture[0] != NULL) {
        deleteTexture(mineTexture[0]);
        mineTexture[0] = NULL;
    }
    if (mineTexture[1] != NULL) {
        deleteTexture(mineTexture[1]);
        mineTexture[1] = NULL;
    }
    freeExplosions();
    clearScreen();
    clearRewards();
    free(mainSpaceShip);
    mainSpaceShip = NULL;
    stopMusic();
    playMenuMusic();
}


// Space Ship Shooting ...

void shootBullet() {
    if (powerBulletActive != 0 && SDL_GetTicks() - powerBulletActive > 500)
        return;
    createNewBullet(mainSpaceShip -> coords.x + mainSpaceShip -> coords.w, mainSpaceShip -> coords.y + (mainSpaceShip -> coords.h / 2), 0, 0, 0);
    playLaserSoundEffect();
}

void shootPowerBullet() {
    if (mainSpaceShip -> specialAmmoAmount <= 0)
        return;
    createNewBullet(mainSpaceShip -> coords.x + mainSpaceShip -> coords.w, mainSpaceShip -> coords.y + (mainSpaceShip -> coords.h / 2), 3, 0, 0);
    playPowerBulletSoundEffect();
    powerBulletActive = 0;
    mainSpaceShip -> specialAmmoAmount--;
}

