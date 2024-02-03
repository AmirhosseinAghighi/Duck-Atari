SDL_Event e;
extern int GameStatus;

void upOrDownArrowsPressed(int state) {
    switch (GameStatus) {
        case Menu:
            menuUpdate(state);
            break;
        case SettingsMenuPage:
            menuSettingsUpdate(state);
            break;
        default:
            break;
    }
}

void leftOrRightArrowsPressed(int state) {
    switch (GameStatus) {
        case SettingsMenuPage:
            settingUpdate(state);
            break;

        default:
            break;
    }
}

void checkKeyStates() {
    const uint8_t *currentKeyStates = SDL_GetKeyboardState( NULL );
    if (GameStatus == Game) {
        int stopSound = 1;
        if (currentKeyStates[SDL_SCANCODE_W]) {
            pushSpaceShipUp();
        }

        if (currentKeyStates[SDL_SCANCODE_S]) {
            pushSpaceShipDown();
        }

        if (currentKeyStates[SDL_SCANCODE_A]) {
            pushSpaceShipLeft();
            stopSound = 0;
        }

        if (currentKeyStates[SDL_SCANCODE_D]) {
            pushSpaceShipRight();
            stopSound = 0;
        }

//        if (currentKeyStates[SDL_SCANCODE_SPACE]) {
//            spacePressed();
//        }

        if (stopSound)
            stopRocketSoundEffect();
    }
    SDL_Delay(30);
}