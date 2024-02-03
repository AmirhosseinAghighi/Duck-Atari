jet *jetsList = NULL;

texture *jetTexture = NULL;
int jetSpawnChance = 10;
Uint32 lastJetSpawnTime = 0;
int spawnedJetCount = 0;
int maxSpawnedJet = 3;
int jetShootChance = 80;
int jetSpawnCooldown = 4000;

SDL_Rect jetCollision[5] = {
        {56, 1, 69, 13},
        {62, 14, 86, 34},
        {10, 48, 150, 30},
        {62, 78, 76, 34},
        {56, 112, 69, 13}
};


void createNewJet() {
    jet *newJet = (jet *) malloc(sizeof(jet));
    newJet -> speed = 8;
    newJet -> data.w = jetTexture -> width;
    newJet -> data.h = jetTexture -> height;
    newJet -> data.x = Width;
    newJet -> data.y = randomNumber(0, Height - jetTexture -> height);
    newJet -> lastShotTime = 0;
    newJet -> next = NULL;
    newJet -> health = 2;


    if (jetsList == NULL) {
        jetsList = newJet;
    } else {
        newJet -> next = jetsList -> next;
        jetsList -> next = newJet;
    }

    elementsOnScreen++;
    spawnedJetCount++;
}

void generateNewJet() {
    if (spawnedJetCount >= maxSpawnedJet)
        return;
    if (SDL_GetTicks() >= jetSpawnCooldown + lastJetSpawnTime) {
        if (randomNumber(1, 100) < jetSpawnChance) {
            createNewJet();
        }
        lastJetSpawnTime = SDL_GetTicks();
    }
}

void deleteJet(jet *curr, jet *prev) {
    if (prev == NULL) {
        jetsList = curr -> next;
    } else {
        prev -> next = curr -> next;
    }
    free(curr);
    elementsOnScreen--;
    spawnedJetCount--;
}

void drawJetCollision(SDL_Rect *data) {
    for (int i = 0; i < 5; ++i) {
        SDL_Rect *collision = &(jetCollision[i]);
        SDL_Rect fillRect = { data -> x + collision -> x, data -> y + collision -> y, collision -> w, collision -> h };
        SDL_SetRenderDrawColor( Render, 50 * i + 10, 10 * i + 10, 0, 0xFF );
        SDL_RenderFillRect( Render, &fillRect );
    }
}

void startJetShootingToSpaceShip(SDL_Rect *data) {
    // we should shoot 3 bomb, 1: current pos of spaceShip, 2: 5 pixel upper than spaceShip, 3: 5 pixel down of spaceShip
    // ax + b = y  -> b = y - ax
    // a = y2 - y1 / x2 - x1
    double deltaX = (mainSpaceShip -> coords.x + (mainSpaceShip -> coords.w / 2) - (data -> x + data -> w / 2));
    if (deltaX > -50)
        return;
    double a = ((double) (mainSpaceShip -> coords.y + (mainSpaceShip -> coords.h / 2)) - (data -> y + data -> h / 2)) / deltaX;
    double b = mainSpaceShip -> coords.y - a * mainSpaceShip -> coords.x;
    SDL_Log("%lf %lf %d %d", a, b, mainSpaceShip -> coords.y - data -> y, mainSpaceShip -> coords.x - data -> x);
    createNewBullet(data -> x, data -> y + (data -> h / 2), 2, a, b);

//    a = (mainSpaceShip -> coords.y + 5 - data -> y) / (mainSpaceShip -> coords.x - data -> x);
//    b = mainSpaceShip -> coords.y - a * mainSpaceShip -> coords.x;
//    createNewBullet(data -> x, data -> y + (data -> h / 2), 2, a, b);
//
//    a = (mainSpaceShip -> coords.y - 5 - data -> y) / (mainSpaceShip -> coords.x - data -> x);
//    b = mainSpaceShip -> coords.y - a * mainSpaceShip -> coords.x;
//    createNewBullet(data -> x, data -> y + (data -> h / 2), 2, a, b);
}

void renderJets() {
    generateNewJet();
    jet *curr = jetsList;
    jet *prev = NULL;
    while (curr != NULL) {
        SDL_RenderCopy(Render, jetTexture -> texture, NULL, &(curr -> data));
        if (scrollSpeed <= 2) {
            curr -> data.x -= curr -> speed * scrollSpeed;
        } else {
            curr -> data.x -= curr -> speed * 2;
        }

        if (checkCustomCollisionWithSpaceShip(&(curr -> data), jetCollision, 5)){
            createExplosion(curr -> data.x, curr -> data.y);
            deleteJet(curr, prev);
            damageSpaceShip(1);
            brokeEngineForATime(150);
            curr = curr->next;
            continue;
        }

        bullet *result = checkCustomCollisionWithBullets(&(curr -> data), jetCollision, 5);
        if (result != NULL){
            curr -> health--;
            if (result -> type == 3)
                curr -> health = 0;
            result -> deleted = 1;
            if (curr -> health == 0) {
                Score += 30; // Smile ;)
                createExplosion(curr -> data.x, curr -> data.y);
                deleteJet(curr, prev);
                curr = curr->next;
                continue;
            }
        }


        int shootCooldown = 1500;
        if (scrollSpeed >= 3) {
            shootCooldown = 1000;
        }
        if (SDL_GetTicks() - curr -> lastShotTime >= shootCooldown) {
            if ( curr -> data.x < Width - curr -> data.w && randomNumber(1, 100) <= jetShootChance) {
                startJetShootingToSpaceShip(&(curr -> data));
            }
            curr -> lastShotTime = SDL_GetTicks();
        }

        if (curr->data.x <= -jetTexture->width) {
            SDL_Log("wtf");
            deleteJet(curr, prev);
            curr = curr->next;
            continue;
        }


        #if debug
            drawJetCollision(&(curr -> data));
        #endif

        prev = curr;
        curr = curr -> next;
    }
}

void renderJetsWithoutMove() {
    jet *curr = jetsList;
    while (curr != NULL) {
        SDL_RenderCopy(Render, jetTexture -> texture, NULL, &(curr -> data));
        curr = curr -> next;
    }
}

void clearJets() {
    jet *curr = jetsList;
    while (curr != NULL) {
        jet *temp = curr;
        free(temp);
        curr = curr -> next;
    }
    jetsList = NULL;
}