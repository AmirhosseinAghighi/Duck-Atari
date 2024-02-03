extern spaceShip *mainSpaceShip;
extern int elementsOnScreen;
extern int maximumElements;
extern texture *mineTexture[2]; // 0 = deactive, 1 = active

int mineSpawnChance = 10;
Uint32 lastMineSpawnTime = 0;
mine *minesList = NULL;
int spawnedMinesCount = 0;
int maxSpawnedMines = 5;
int mineSpawnCoolDown = 5000;

#define mineDefaultTimer 1000 // in ms
#define mineNearTimer 100 // in ms

int isMineNearOfThisY(int y) { // legacy
    mine *curr = minesList;
    while (curr != NULL) {
        if (curr -> data.y + 30 > y && curr -> data.y - 30 - mineTexture[0] -> height < y )
            return 1;
        curr = curr -> next;
    }
    return 0;
}

//int generateNewMineY() { LEGACY
//    int yCoord= randomNumber(0, Height - mineTexture[0] -> height);
//    int count = 0;
//    while (isMineNearOfThisY(yCoord)) {
//        if (count >= 10)
//            return 0;
//        yCoord = randomNumber(0, Height - mineTexture[0] -> height);
//        count++;
//    }
//    return yCoord;
//}

void generateNewMine() {
    if (SDL_GetTicks() <= mineSpawnCoolDown + lastMineSpawnTime || spawnedMinesCount >= maxSpawnedMines) {
        return;
    }
    lastMineSpawnTime = SDL_GetTicks();
    if (elementsOnScreen < maximumElements && randomNumber(1, 100) <= mineSpawnChance) {
        if (mineTexture[0] == NULL)
            mineTexture[0] = loadTexture("../images/Game/mine.png");
        if (mineTexture[1] == NULL)
            mineTexture[1] = loadTexture("../images/Game/mineActive.png");

        mine *newMine = (mine *) malloc(sizeof(mine));
        newMine -> next = NULL;
        newMine -> active = 0;
        newMine -> startTime = SDL_GetTicks();
        newMine -> data.x = Width;
//        newMine -> data.y = generateNewMineY(); LEGACY
        newMine -> data.y = randomNumber(0, Height - mineTexture[0] -> height);
        newMine -> data.w = mineTexture[0] -> width;
        newMine -> data.h = mineTexture[0] -> height;
        newMine -> speed = randomNumber(1, 3);

        if (minesList == NULL) {
            minesList = newMine;
        } else {
            newMine -> next = minesList -> next;
            minesList -> next = newMine;
        }


        elementsOnScreen++;
        spawnedMinesCount++;
    }
}

//int checkCollisionBetweenMineAnd(SDL_Rect *data) {
//    for (int i = 0; i < 7; ++i) {
//        if ( ((data -> y + data -> h <= mainSpaceShip -> coords.y + mainSpaceShip -> collision[i].y) || (data -> y >= mainSpaceShip -> coords.y + mainSpaceShip -> collision[i].y + mainSpaceShip -> collision[i].h) || (data -> x + data -> w <= mainSpaceShip -> coords.x + mainSpaceShip -> collision[i].x) || (data -> x >= mainSpaceShip -> coords.x + mainSpaceShip -> collision[i].x + mainSpaceShip -> collision[i].w)) == 0 )
//            return 1;
//    }
//    return 0;
//}

void deleteMine(mine *curr, mine *prev) {
    if (prev == NULL) {
        minesList = curr -> next;
    } else {
        prev -> next = curr -> next;
    }
    mine *temp = curr;
    free(temp);
    elementsOnScreen--;
    spawnedMinesCount--;
}

extern void damageSpaceShip();
extern void brokeEngineForATime();
void drawMines() {
    generateNewMine();

    mine *curr = minesList;
    mine *prev = NULL;
    #if debug
        int dbugMineCount = 0;
    #endif
    while (curr != NULL) {
        #if debug
            SDL_Log("Go for the next mine render, %d / %d", dbugMineCount, elementsOnScreen);
        #endif
        curr -> data.x -= curr -> speed * scrollSpeed;

        if (curr -> data.x <= -mineTexture[0] -> width) {
            #if debug
                SDL_Log("---------deleting mine because it goes out of screen");
            #endif
            deleteMine(curr, prev);
            curr = curr -> next;
            continue;
        }

        bullet *result = checkBulletCollision(&(curr -> data), 0);
        if (result != NULL) {
            #if debug
                SDL_Log("---------deleting mine because bullet");
            #endif
            Score += 10; // Smile ;)
            createExplosion(curr -> data.x, curr -> data.y);
            deleteMine(curr, prev);
            result -> deleted = 1;
            curr = curr->next;
            continue;
        }

        if (checkCollision(&(curr -> data))){
            #if debug
                SDL_Log("---------deleting mine because collision");
            #endif
            createExplosion(curr -> data.x, curr -> data.y);
            deleteMine(curr, prev);
            damageSpaceShip(1);
            brokeEngineForATime(50);
            curr = curr->next;
            continue;
        }


        #if debug
            SDL_Log("go for rendering %d", curr -> active);
        #endif
        if (curr -> active) {
            SDL_RenderCopy(Render, mineTexture[0] -> texture, NULL, &(curr -> data));
        } else {
            SDL_RenderCopy(Render, mineTexture[1] -> texture, NULL, &(curr -> data));
        }

        #if debug
            SDL_Log("rendered successfully");
        #endif

        if (calculateDistance(mainSpaceShip -> coords.x, mainSpaceShip -> coords.y, curr -> data.x, curr -> data.y) <= 300) {
            if (SDL_GetTicks() - curr -> startTime >= mineNearTimer) {
                curr -> startTime = SDL_GetTicks();
                curr -> active = !curr -> active;
            }
        } else {
            if (SDL_GetTicks() - curr -> startTime >= mineDefaultTimer) {
                curr -> startTime = SDL_GetTicks();
                curr -> active = !curr -> active;
            }
        }


        #if debug
            SDL_Log("handeled mine activate check");
        #endif

        #if debug
            SDL_SetRenderDrawColor( Render, 255, 255, 0, 30 );
            SDL_RenderFillRect( Render, &(curr -> data) );
        #endif


        #if debug
            SDL_Log("going for next loop");
        #endif

        prev = curr;
        curr = curr -> next;

        #if debug
            dbugMineCount++;
        #endif
    }

}



void renderMinesWithoutMove() {
    mine *curr = minesList;
    while (curr != NULL) {
        SDL_RenderCopy(Render, mineTexture[curr -> active] -> texture, NULL, &(curr -> data));
        curr = curr -> next;
    }
}


void clearMines() {
    mine *curr = minesList;
    while (curr != NULL) {
        mine *temp = curr;
        free(temp);
        curr = curr -> next;
    }
    minesList = NULL;
}