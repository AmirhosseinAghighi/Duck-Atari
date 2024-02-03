extern SDL_Window *Window;
extern SDL_Renderer *Render;
SDL_Surface *icon = NULL;

int startUp() {
    initializeDisplaymode();
    return 1;
}

int init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { // Init everything from SDL ( We should change these with our needs later ( it's good to make a function for it )
        printf("SDL could not initialize! Error: %s\n", SDL_GetError());
        return -1;
    }

    startUp(); // SDL should be initialized at first !!!
    Window = SDL_CreateWindow("Duck Atari", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_BORDERLESS | SDL_RENDERER_PRESENTVSYNC); // SDL_WINDOW_FULLSCREEN
    if (Window == NULL) {
        printf("Faild to create window: SDL_ERROR: %s\n", SDL_GetError());
        return -2;
    }

    // creating icon for it...
    icon = IMG_Load("../images/icon.png");
    if (icon != NULL) {
        SDL_SetWindowIcon(Window, icon);
    }

    Render = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if( Render == NULL )
    {
        SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return -3;
    }
    SDL_SetRenderDrawColor(Render, 0xFF, 0xFF, 0xFF, 0xFF);

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        SDL_Log("There was a problem in IMG_init function, ERROR: %s\n", IMG_GetError());
        return -4;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 4, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return -5;
    }

    if (TTF_Init() == -1) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return -6;
    }
}

extern TTF_Font *gameFont;
extern void unloadLeaderBoard();
int Destroy() {
    if (icon != NULL)
        SDL_FreeSurface(icon);
    unloadLeaderBoard();
    freeTextures();
    DestroyAnySound();
    SDL_DestroyWindow(Window);
    Window = NULL;
    SDL_DestroyRenderer(Render);
    Render = NULL;
    TTF_CloseFont(gameFont);
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}