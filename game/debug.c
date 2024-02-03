extern spaceShip *mainSpaceShip;

void drawCollisions() {
    for (int i = 0; i < 7; ++i) {
        SDL_Rect *collison = &(mainSpaceShip -> collision[i]);
        SDL_Rect fillRect = { mainSpaceShip -> coords.x + collison -> x, mainSpaceShip -> coords.y + collison -> y, collison -> w, collison -> h };
        SDL_SetRenderDrawColor( Render, 200, 20 * i, 20 * i, 0xFF );
        SDL_RenderFillRect( Render, &fillRect );
    }
}