texture *explosionFrames[6];
texture *smokeFrames[6];
void loadExplosionsTextures() {
    explosionFrames[0] = loadTexture("../images/explosion/1.png");
    explosionFrames[1] = loadTexture("../images/explosion/2.png");
    explosionFrames[2] = loadTexture("../images/explosion/3.png");
    explosionFrames[3] = loadTexture("../images/explosion/4.png");
    explosionFrames[4] = loadTexture("../images/explosion/5.png");
    explosionFrames[5] = loadTexture("../images/explosion/6.png");

    smokeFrames[0] = loadTexture("../images/smoke/1.png");
    smokeFrames[1] = loadTexture("../images/smoke/2.png");
    smokeFrames[2] = loadTexture("../images/smoke/3.png");
    smokeFrames[3] = loadTexture("../images/smoke/4.png");
    smokeFrames[4] = loadTexture("../images/smoke/5.png");
    smokeFrames[5] = loadTexture("../images/smoke/6.png");
}

void freeExplosions() {
    for (int i = 0; i < 5; ++i) {
        deleteTexture(explosionFrames[i]);
        explosionFrames[i] = NULL;
        deleteTexture(smokeFrames[i]);
        smokeFrames[i] = NULL;
    }
}

explosion *Explosions = NULL;

void createNewExplosionNode(int x, int y, int type) {
    explosion *newExplosion = (explosion *) malloc(sizeof(explosion));
    newExplosion -> frame = 0;
    newExplosion -> data.x = x;
    newExplosion -> data.y = y;
    newExplosion -> data.w = explosionFrames[0] -> width;
    newExplosion -> data.h = explosionFrames[0] -> height;
    newExplosion -> next = NULL;
    newExplosion -> type = type;

    if (Explosions == NULL) {
        Explosions = newExplosion;
    } else {
        newExplosion -> next = Explosions -> next;
        Explosions -> next = newExplosion;
    }
}

void createExplosion(int x, int y) {
    createNewExplosionNode(x, y, 0);
    playExplosionSoundEffect();
}

void createSmoke(int x, int y) {
    createNewExplosionNode(x, y, 1);
}

void deleteExplosion(explosion *curr, explosion *prev) {
    if (prev == NULL) {
        Explosions = curr -> next;
    } else {
        prev -> next = curr -> next;
    }
    free(curr);
}

void drawExplosions() {
    explosion *curr = Explosions;
    explosion *prev = NULL;

    while (curr != NULL) {
        if (curr -> frame >= 60) {
            deleteExplosion(curr, prev);
            curr = curr -> next;
            continue;
        }
        int selectedFrame = curr -> frame / 10;
        curr -> frame += 4;
        if (curr -> type == 0) {
            SDL_RenderCopy(Render, explosionFrames[selectedFrame] -> texture, NULL, &(curr -> data));
        } else if (curr -> type == 1) {
            SDL_RenderCopy(Render, smokeFrames[selectedFrame] -> texture, NULL, &(curr -> data));
        }
        prev = curr;
        curr = curr -> next;
    }
}