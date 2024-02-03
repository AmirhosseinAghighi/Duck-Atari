extern int checkCollision();
extern bullet *checkBulletCollision();

int checkCustomCollisionWithSpaceShip(SDL_Rect *data, SDL_Rect customCollisionArr[], int size) {
    for (int i = 0; i < size; ++i) {
        SDL_Rect *collision = &(customCollisionArr[i]);
        SDL_Rect collisionRect = { data -> x + collision -> x, data -> y + collision -> y, collision -> w, collision -> h };
        if (checkCollision(&collisionRect))
            return 1;
    }
    return 0;
}

bullet *checkCustomCollisionWithBullets(SDL_Rect *data, SDL_Rect customCollisionArr[], int size) {
    for (int i = 0; i < size; ++i) {
        SDL_Rect *collision = &(customCollisionArr[i]);
        SDL_Rect collisionRect = { data -> x + collision -> x, data -> y + collision -> y, collision -> w, collision -> h };
        bullet *result = checkBulletCollision(&collisionRect, 0);
        if (result != NULL)
            return result;
    }
    return NULL;
}