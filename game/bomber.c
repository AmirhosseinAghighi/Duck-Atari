bomber *bombersList = NULL;

texture *bomberTexture = NULL;
int bomberSpawnChance = 90;
Uint32 lastBomberSpawnTime = 0;
int spawnedBomberCount = 0;
int maxSpawnedBomber = 2;
int bomberSpawnCoolDown = 7000;


void createNewBomber(int y, int direction) {
    bomber *newBomber = (bomber *) malloc(sizeof(bomber));
    newBomber -> speed = 2;
    newBomber -> direction = direction;
    newBomber -> lastShotTime = 0;
    newBomber -> data.w = bomberTexture -> width;
    newBomber -> data.h = bomberTexture -> height;
    newBomber -> data.x = Width;
    newBomber -> data.y = y;
    newBomber -> next = NULL;
    newBomber -> ammoAmount = 5;
    newBomber -> status = 0;
    newBomber -> health = 4;

    if (bombersList == NULL) {
        bombersList = newBomber;
    } else {
        newBomber -> next = bombersList -> next;
        bombersList -> next = newBomber;
    }

    elementsOnScreen++;
    spawnedBomberCount++;
}

void generateNewBomber() {
    if (spawnedBomberCount > maxSpawnedBomber)
        return;
    if (SDL_GetTicks() >= bomberSpawnCoolDown + lastBomberSpawnTime) {
        if (randomNumber(1, 100) <= bomberSpawnChance) {
            if (randomNumber(1, 100) <= 50) {
                createNewBomber(-bomberTexture -> height, 1);
            } else {
                createNewBomber(Height + bomberTexture -> height, -1);
            }
        }
        lastBomberSpawnTime = SDL_GetTicks();
    }
}

void deleteBomber(bomber *curr, bomber *prev) {
    if (prev == NULL) {
        bombersList = curr -> next;
    } else {
        prev -> next = curr -> next;
    }
    free(curr);
    elementsOnScreen--;
    spawnedBomberCount--;
}


void renderBombers() {
    generateNewBomber();
    bomber *curr = bombersList;
    bomber *prev = NULL;
    while (curr != NULL) {

        bullet *bulletCollision = checkBulletCollision(&(curr -> data), 0);
        if (bulletCollision != NULL) {
            curr -> health--;
            if (bulletCollision -> type == 3) {
                curr -> health = 0;
            }
            bulletCollision -> deleted = 1;
            if (curr -> health <= 0) {
                createExplosion(curr -> data.x, curr -> data.y);
                Score += 50; // Smile ;)
                deleteBomber(curr, prev);
                curr = curr->next;
                continue;
            } else {
                createSmoke(bulletCollision -> data.x + bulletCollision -> data.w, bulletCollision -> data.y);
            }
        }

        if (checkCollision(&(curr -> data))){
            createExplosion(curr -> data.x, curr -> data.y);
            deleteBomber(curr, prev);
            damageSpaceShip(1);
            brokeEngineForATime(250);
            curr = curr->next;
            continue;
        }

        SDL_RenderCopy(Render, bomberTexture -> texture, NULL, &(curr -> data));
        curr -> data.x -= 2 * scrollSpeed;
        curr -> data.y += curr -> speed * curr -> direction * scrollSpeed;
        if ((curr -> direction < 0 && curr -> data.y <= -bomberTexture -> height) || (curr -> direction > 0 && curr -> data.y >= Height + bomberTexture -> height)) {
            deleteBomber(curr, prev);
            curr = curr -> next;
            continue;
        } else {
            int bomberShootCooldown = 2500;
            if (scrollSpeed > 3) {
                bomberShootCooldown = 1200;
            } else if (scrollSpeed > 5) {
                bomberShootCooldown = 800;
            } else if (scrollSpeed > 7) {
                bomberShootCooldown = 500;
            }
            if (curr -> ammoAmount > 0 && SDL_GetTicks() - curr -> lastShotTime >= bomberShootCooldown && curr -> data.y < Height - curr -> data.h && curr -> data.y >= 0 && randomNumber(1, 100) <= 20) {
                if (curr -> status) {
                    createNewBullet(curr -> data.x, curr -> data.y, 1, 0, 0);
                    curr -> status = 0;
                }
                else{
                    createNewBullet(curr -> data.x, curr -> data.y + curr -> data.h -bulletTexturesByTypes[1] -> height, 1, 0, 0);
                    curr -> status = 1;
                }
                curr -> ammoAmount--;
                curr -> lastShotTime = SDL_GetTicks();
            }
        }
        prev = curr;
        curr = curr -> next;
    }
}

void renderBombersWithoutMove() {
    bomber *curr = bombersList;
    while (curr != NULL) {
        SDL_RenderCopy(Render, bomberTexture -> texture, NULL, &(curr -> data));
        curr = curr -> next;
    }
}

void clearBombers() {
    bomber *curr = bombersList;
    while (curr != NULL) {
        bomber *temp = curr;
        free(temp);
        curr = curr -> next;
    }
    bombersList = NULL;
}