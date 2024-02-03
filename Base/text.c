TTF_Font *gameFont = NULL;

SDL_Texture *loadFromRenderedText(char *string, SDL_Color color) {

    if (gameFont == NULL) {
        gameFont = TTF_OpenFont( "../Fonts/dpcomic.ttf", 28 );
        if (gameFont == NULL) {
            SDL_Log("failed to load font !! error: %s", SDL_GetError());
            return NULL;
        }
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(gameFont, string, color);
    if (textSurface == NULL) {
        SDL_Log("there was an error in creating textureSurface !!! error: %s", SDL_GetError());
        return NULL;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(Render, textSurface);

    if( textTexture == NULL )
    {
        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }

    SDL_FreeSurface( textSurface );

    return textTexture;
}