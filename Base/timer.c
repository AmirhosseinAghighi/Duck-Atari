//Uint32 startTime = 0;
//Uint32 pausedTicks = 0;

//int timerPaused = 0;
//int timerStarted = 0;

void startTimer(Uint32 *startTime, Uint32 *pausedTicks, int *timerPaused, int * timerStarted) {
    *timerStarted = 1;
    *timerPaused = 0;
    *startTime = SDL_GetTicks();
    *pausedTicks = 0;
}

void stopTimer(Uint32 *startTime, Uint32 *pausedTicks, int *timerPaused, int * timerStarted) {
    *timerStarted = 0;
    *timerPaused = 0;
    *startTime = 0;
    *pausedTicks = 0;
}

void togglePauseTimer(Uint32 *startTime, Uint32 *pausedTicks, int *timerPaused, int *timerStarted) {
    if (*timerStarted && !*timerPaused) {
        *timerPaused = 1;
        *pausedTicks = SDL_GetTicks() - *startTime;
        *startTime = 0;
    } else if (*timerStarted && *timerPaused) {
        *timerPaused = 0 ;
        *startTime = SDL_GetTicks() - *startTime;
        *pausedTicks = 0;
    }
}

Uint32 timePassedInTimer(Uint32 *startTime, Uint32 *pausedTicks, int *timerPaused, int *timerStarted) {
    if (*timerStarted) {
        if (*timerPaused) {
            return *pausedTicks;
        } else {
            return SDL_GetTicks() - *startTime;
        }
    } else {
        return 0;
    }
}

int isTimerStarted(int *timerStarted) {
    return *timerStarted;
}

int isTimerPaused(int *timerPaused) {
    return *timerPaused;
}