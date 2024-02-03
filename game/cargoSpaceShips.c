//extern int elementsOnScreen;
//extern int maximumElements;
extern texture *cargoSpaceShipTexture;

SDL_Rect cargoSpaceShipCollision[3] = {
        {93, 4, 63, 86},
        {0, 90, 252, 75},
        {93, 165, 63, 86}
};

int cargoSpawnChance = 10;
Uint32 lastCargoSpawnTime = 0; // first time, it will spawn after 1 minute
cargoSpaceShip *cargoSpaceShipsList = NULL;
int spawnedCargoCount = 0;
int maxSpawnedCargo = 1;
int cargoSpawnCooldown = 15000;

int isCargoNearOfThisY(int y) { // legacy
    cargoSpaceShip *curr = cargoSpaceShipsList;
    while (curr != NULL) {
        if (curr -> data.y + 30 > y && curr -> data.y - 30 - cargoSpaceShipTexture -> height < y )
            return 1;
        curr = curr -> next;
    }
    return 0;
}

//int generateNewCargoY() {
//    int yCoord= randomNumber(0, Height - cargoSpaceShipTexture -> height);
//    int count = 0;
//    while (isCargoNearOfThisY(yCoord)) {
//        if (count >= 10)
//            return 0;
//        yCoord = randomNumber(0, Height - cargoSpaceShipTexture -> height);
//        count++;
//    }
//    return yCoord;
//}

void generateNewCargo() {
    if (SDL_GetTicks() <= cargoSpawnCooldown + lastCargoSpawnTime || spawnedCargoCount >= maxSpawnedCargo) {
        return;
    }
    lastCargoSpawnTime = SDL_GetTicks();
    if (elementsOnScreen < maximumElements && randomNumber(1, 100) <= cargoSpawnChance) {
        if (cargoSpaceShipTexture == NULL)
            cargoSpaceShipTexture = loadTexture("../images/Game/cargoSpaceShip.png");

        cargoSpaceShip *newCargoSpaceShip = (cargoSpaceShip *) malloc(sizeof(cargoSpaceShip));
        newCargoSpaceShip -> next = NULL;
        newCargoSpaceShip -> data.x = Width;
//        newCargoSpaceShip -> data.y = generateNewCargoY(); LEGACY
        newCargoSpaceShip -> data.y = randomNumber(0, Height - cargoSpaceShipTexture -> height);
        newCargoSpaceShip -> data.w = cargoSpaceShipTexture -> width;
        newCargoSpaceShip -> data.h = cargoSpaceShipTexture -> height;
        newCargoSpaceShip -> speed = randomNumber(1, 3);
        newCargoSpaceShip -> degree = 0;
        newCargoSpaceShip -> health = 3;

        if (cargoSpaceShipsList == NULL) {
            cargoSpaceShipsList = newCargoSpaceShip;
        } else {
            newCargoSpaceShip -> next = cargoSpaceShipsList -> next;
            cargoSpaceShipsList -> next = newCargoSpaceShip;
        }


        elementsOnScreen++;
        spawnedCargoCount++;
    }
}

void deleteCargoSpaceShip(cargoSpaceShip *curr, cargoSpaceShip *prev, int reward) {
    if (prev == NULL) {
        cargoSpaceShipsList = curr -> next;
    } else {
        prev -> next = curr -> next;
    }
    if (reward)
        generateReward(curr -> data.x + (curr -> data.w / 2), curr -> data.y + (curr -> data.h / 2));
    free(curr);
    elementsOnScreen--;
    spawnedCargoCount--;
}


void drawCargoSpaceShipsCollision(SDL_Rect *data) {
//    SDL_Rect fillRect = { x, y, w, h };

    for (int i = 0; i < 3; ++i) {
        SDL_Rect *collision = &(cargoSpaceShipCollision[i]);
        SDL_Rect fillRect = { data -> x + collision -> x, data -> y + collision -> y, collision -> w, collision -> h };
        SDL_SetRenderDrawColor( Render, 0, 70 * i, 70 * i, 0xFF );
        SDL_RenderFillRect( Render, &fillRect );
    }
}


void drawCargoSpaceShips() {
    generateNewCargo();

    cargoSpaceShip *curr = cargoSpaceShipsList;
    cargoSpaceShip *prev = NULL;
    while (curr != NULL) {
        #if debug
            SDL_Log("Go for the next mine render");
        #endif
        curr->data.x -= curr->speed * scrollSpeed;

        if (curr->data.x <= -cargoSpaceShipTexture->width) {
            #if debug
                SDL_Log("---------deleting cargo because it's out of screen");
            #endif
            deleteCargoSpaceShip(curr, prev, 0);
            curr = curr->next;
            continue;
        }

        bullet *bulletCollision = checkCustomCollisionWithBullets(&(curr -> data), cargoSpaceShipCollision, 3);
        if (bulletCollision != NULL) {
            curr -> health--;
            if (bulletCollision -> type == 3)
                curr -> health = 0;
            bulletCollision -> deleted = 1;
            if (curr -> health == 0) {
                #if debug
                    SDL_Log("---------deleting cargo because health = 0");
                #endif
                createExplosion(curr->data.x + (curr -> data.w / 2), curr->data.y + (curr -> data.h / 2));
                deleteCargoSpaceShip(curr, prev, 1);
                curr = curr->next;
                continue;
            } else {
                createSmoke(bulletCollision -> data.x + bulletCollision -> data.w, bulletCollision -> data.y);
            }
        }

        if (checkCustomCollisionWithSpaceShip(&(curr -> data), cargoSpaceShipCollision, 3)) {
            #if debug
                        SDL_Log("---------deleting cargo because collision");
            #endif
            createExplosion(curr->data.x + (curr -> data.w / 2), curr->data.y + (curr -> data.h / 2));
            deleteCargoSpaceShip(curr, prev, 0);
            damageSpaceShip(1);
            brokeEngineForATime(50);
            curr = curr->next;
            continue;
        }


//        SDL_RenderCopy(Render, cargoSpaceShipTexture->texture, NULL, &(curr->data));
        SDL_RenderCopyEx(Render, cargoSpaceShipTexture->texture, NULL, &(curr->data), curr -> degree, NULL, SDL_FLIP_NONE);
        curr -> degree   += 1;
        if (curr -> degree == 360)
            curr -> degree = 0;

        #if debug
                SDL_Log("rendered successfully");
                SDL_Log("going for next loop");
        #endif

        #if debug
            drawCargoSpaceShipsCollision(&(curr -> data));
        #endif

        #if debug
                SDL_Log("going for next loop");
        #endif

        prev = curr;
        curr = curr->next;
    }

}


void renderCargosWithoutMove() {
    cargoSpaceShip *curr = cargoSpaceShipsList;
    while (curr != NULL) {
        SDL_RenderCopy(Render, cargoSpaceShipTexture -> texture, NULL, &(curr -> data));
        curr = curr -> next;
    }
}

void clearCargos() {
    cargoSpaceShip *curr = cargoSpaceShipsList;
    while (curr != NULL) {
        cargoSpaceShip *temp = curr;
        free(temp);
        curr = curr -> next;
    }
    cargoSpaceShipsList = NULL;
}