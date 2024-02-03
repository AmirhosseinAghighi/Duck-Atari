int Width;
int Height;

void initializeDisplaymode() {
    // https://stackoverflow.com/questions/33393528/how-to-get-screen-size-in-sdl
    SDL_DisplayMode DM;
    int res = SDL_GetCurrentDisplayMode(0, &DM);
//    printf("%d", res);
    Width = DM.w;
    Height = DM.h;
//    Width = 800;
//    Height = 600;
}

void SetGlobalRect(w, h, x, y) {
    extern SDL_Rect globalRect;
    globalRect.w = w;
    globalRect.h = h;
    globalRect.x = x;
    globalRect.y = y;
}