texture *gameoverGlass = NULL;
texture *gameOverText = NULL;
texture *gameOverEnterNicknameText = NULL;
char playerNickname[21] = {' '};
SDL_Texture *playerNicknameTexture = NULL;

void loadGameOverTextures();
void gameOver() {
    GameStatus = Gameover;
    loadGameOverTextures();
    stopRocketSoundEffect();
    SDL_StartTextInput();
}

void loadGameOverTextures() {
    if (gameoverGlass == NULL) {
        gameoverGlass = loadTexture("../images/glass.png");
        if (gameoverGlass == NULL) {
            SDL_Log("unable to load glass texture for game over !!! %s", SDL_GetError());
            return;
        }
    }

    if (gameOverText == NULL) {
        gameOverText = loadTexture("../images/menu/gameover.png");
        if (gameOverText == NULL) {
            SDL_Log("unable to load gameover texture for game over !!! %s", SDL_GetError());
            return;
        }
    }

    if (gameOverEnterNicknameText == NULL) {
        gameOverEnterNicknameText = loadTexture("../images/menu/nickname.png");
        if (gameOverEnterNicknameText == NULL) {
            SDL_Log("unable to load nickname texture for game over !!! %s", SDL_GetError());
            return;
        }
    }
};

void renderGameOverScreen() {
    SDL_RenderCopy(Render, gameoverGlass -> texture, NULL, NULL);

    SDL_Rect pos = {Width / 2 - gameOverText -> width / 2, 50, gameOverText -> width, gameOverText -> height};
    SDL_RenderCopy(Render, gameOverText -> texture, NULL, &pos);

    pos.x = Width / 2 - gameOverEnterNicknameText -> width / 2;
    pos.y = gameOverEnterNicknameText -> height + 50;
    SDL_RenderCopy(Render, gameOverEnterNicknameText -> texture, NULL, &pos);

    if (playerNicknameTexture != NULL) {
        pos.x = Width / 2 - (strlen(playerNickname) * 40);
        pos.y = 2 * (gameOverEnterNicknameText -> height) + 50;
        pos.w = strlen(playerNickname) * 80;
        SDL_RenderCopy(Render, playerNicknameTexture, NULL, &(pos));
    }
}

//SDL_Color scoreColor = {255, 255, 255};
//SDL_Texture *textTexture = loadFromRenderedText(string, scoreColor);
//SDL_DestroyTexture(textTexture);

void updatePlayerNickNameTexture() {
    if (playerNicknameTexture != NULL) {
        SDL_DestroyTexture(playerNicknameTexture);
        playerNicknameTexture = NULL;
    }

    SDL_Color scoreColor = {42, 157, 143};
    playerNicknameTexture = loadFromRenderedText(playerNickname, scoreColor);
}