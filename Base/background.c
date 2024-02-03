extern int scrollSpeed;
double scrollingBackgroundOffset = 1;
double scrolling_small_BackgroundOffset = 1;
double scrolling_medium_BackgroundOffset = 1;
texture *menuBackground;
texture *small_Background;
texture *medium_Background;

void createMainBackground() {
    scrollingBackgroundOffset -= 2 * scrollSpeed;
    if (scrollingBackgroundOffset + menuBackground -> width <= 2)
        scrollingBackgroundOffset = 0;

    SDL_FRect pos = {scrollingBackgroundOffset, 0, menuBackground -> width, menuBackground -> height};
    SDL_RenderCopyF(Render, menuBackground -> texture, NULL, &(pos));


    if (scrollingBackgroundOffset != 0) {
        pos.x = scrollingBackgroundOffset + pos.w;
        SDL_RenderCopyF(Render, menuBackground -> texture, NULL, &(pos));
    }
}


void createMediumStarsBackground() {
    scrolling_medium_BackgroundOffset -= 1 * scrollSpeed;
    if (scrolling_medium_BackgroundOffset + medium_Background -> width <= 2)
        scrolling_medium_BackgroundOffset = 0;

    SDL_FRect pos = {scrolling_medium_BackgroundOffset, 0, medium_Background -> width, medium_Background -> height};
    SDL_RenderCopyF(Render, medium_Background -> texture, NULL, &(pos));


    if (scrolling_medium_BackgroundOffset != 0) {
        pos.x = scrolling_medium_BackgroundOffset + pos.w;
        SDL_RenderCopyF(Render, medium_Background -> texture, NULL, &(pos));
    }
}

void createSmallStarsBackground() {
    scrolling_small_BackgroundOffset -= 1 * scrollSpeed;
    if (scrolling_small_BackgroundOffset + small_Background -> width == 2)
        scrolling_small_BackgroundOffset = 0;

    SDL_FRect pos = {scrolling_small_BackgroundOffset, 0, small_Background -> width, small_Background -> height};
    SDL_RenderCopyF(Render, small_Background -> texture, NULL, &(pos));


    if (scrolling_small_BackgroundOffset != 0) {
        pos.x = scrolling_small_BackgroundOffset + pos.w;
        SDL_RenderCopyF(Render, small_Background -> texture, NULL, &(pos));
    }
}

void createBackground() {
    createMainBackground();
    createSmallStarsBackground();
//    createMediumStarsBackground();
}