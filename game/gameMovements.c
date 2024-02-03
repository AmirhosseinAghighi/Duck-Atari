extern int GameStatus;

void pushSpaceShipUp() {
    if (GameStatus == Game) {
        if (SDL_GetTicks() - brokenEngineTime <= brokenEngineTimer) {
            renderCorruptedBackfire();
            return;
        } else {
            fixEngine();
        }
        if (mainSpaceShip -> coords.y > 0)
            mainSpaceShip -> coords.y -= mainSpaceShip -> Hspeed;
    }
}

void pushSpaceShipDown() {
    if (GameStatus == Game) {
        if (SDL_GetTicks() - brokenEngineTime <= brokenEngineTimer) {
            renderCorruptedBackfire();
            return;
        } else {
            fixEngine();
        }
        if (mainSpaceShip->coords.y < Height - mainSpaceShip -> coords.w)
            mainSpaceShip->coords.y += mainSpaceShip->Hspeed;
    }
}


void pushSpaceShipLeft() {
    if (GameStatus == Game) {
        if (SDL_GetTicks() - brokenEngineTime <= brokenEngineTimer) {
            renderCorruptedBackfire();
            return;
        } else {
            fixEngine();
        }
        if (haveEnoughFuel(1) && mainSpaceShip->coords.x > (mainSpaceShip -> backfire1Texture -> width / 4)){
            mainSpaceShip->coords.x -= mainSpaceShip->Vspeed;
            costFuel(1);
            renderBackfire();
            playRocketSoundEffect();
        }
    }
}

void pushSpaceShipRight() {
    if (GameStatus == Game) {
        if (SDL_GetTicks() - brokenEngineTime <= brokenEngineTimer) {
            renderCorruptedBackfire();
            return;
        } else {
            fixEngine();
        }
        if (haveEnoughFuel(1) &&mainSpaceShip->coords.x < Width - mainSpaceShip -> coords.w) {
            mainSpaceShip->coords.x += mainSpaceShip->Vspeed;
            costFuel(1);
            renderBackfire();
            playRocketSoundEffect();
        }
    }
}

Uint32 shootingCoolDownStart = 0;
void spacePressed() {
    if (GameStatus == Game) {
        int shootingCooldown = 200;
        if (scrollSpeed >= 5) {
            shootingCooldown = 100;
        }

        if (SDL_GetTicks() - shootingCoolDownStart >= shootingCooldown) {
            shootingCoolDownStart = SDL_GetTicks();
            shootBullet();
        }
    }
}