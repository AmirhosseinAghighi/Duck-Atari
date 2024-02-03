bullet *bulletsList = NULL;

texture *bulletTexturesByTypes[4];
int bulletsSpeedByType[4] = {10, -15, -20, 12};

void createNewBullet(int x, int y, int type, double a, double b) {
    bullet *newBullet = (bullet *) malloc(sizeof(bullet));
    newBullet -> data.w = bulletTexturesByTypes[type] -> width;
    newBullet -> data.h = bulletTexturesByTypes[type] -> height;
    newBullet -> data.x = x;
    newBullet -> data.y = y - (newBullet -> data.h / 2);
    newBullet -> type = type;
    newBullet -> a = a;
    newBullet -> b = b;
    newBullet -> next = NULL;
    newBullet -> speed = bulletsSpeedByType[type];
    newBullet -> deleted = 0;

    if (bulletsList == NULL) {
        bulletsList = newBullet;
    } else {
        newBullet -> next = bulletsList -> next;
        bulletsList -> next = newBullet;
    }
}

void deleteBullet(bullet *prev, bullet *curr) {
    if (prev == NULL) {
        bulletsList = curr -> next;
    } else {
        prev -> next = curr -> next;
    }
    free(curr);
}

extern void createSmoke();
void renderBullets() {
    bullet *prev = NULL;
    bullet *curr = bulletsList;
    while (curr != NULL) {
        if ((curr -> deleted && curr -> type != 3) || curr->data.x >= Width + curr -> data.w) {
            deleteBullet(prev, curr);
            curr = curr -> next;
            continue;
        }
        SDL_RenderCopy(Render, bulletTexturesByTypes[curr -> type] -> texture, NULL, &(curr -> data));
        if (scrollSpeed >= 3) {
            curr -> data.x += curr -> speed * scrollSpeed;
        } else {
            curr -> data.x += curr -> speed * 3;
        }
        if (curr -> a != 0 || curr -> b != 0)
            curr -> data.y = (int)((curr -> a * curr -> data.x) + curr -> b);
        prev = curr;
        curr = curr -> next;
    }
}

bullet *checkBulletCollision(SDL_Rect *data, int type) {
    bullet *curr = bulletsList;
    while (curr != NULL) {
        if (type != curr -> type && curr -> type != 3) { // as we use this for just enemy's ...
            curr = curr -> next;
            continue;
        }
        if ( ((data -> y + data -> h <= curr -> data.y) || (data -> y >= curr -> data.y + curr -> data.h) || (data -> x + data -> w <= curr -> data.x) || (data -> x >= curr -> data.x + curr -> data.w)) == 0 )
            return curr;

        if (curr -> type == 3 && calculateDistance(data -> x, data -> y, curr -> data.x, curr -> data.y) <= 150) {
            return curr;
        }
        curr = curr -> next;
    }
    return curr;
}

bullet *checkBulletCollisionExcept(SDL_Rect *data, int type) {
    bullet *curr = bulletsList;
    while (curr != NULL) {
        if (type == curr -> type) {
            curr = curr -> next;
            continue;
        }
        if ( ((data -> y + data -> h <= curr -> data.y) || (data -> y >= curr -> data.y + curr -> data.h) || (data -> x + data -> w <= curr -> data.x) || (data -> x >= curr -> data.x + curr -> data.w)) == 0 )
            return curr;

        curr = curr -> next;
    }
    return curr;
}