GameMenu *menuHead = NULL;
GameMenu *lastMenuOption = NULL;
void createMenuNode(char *Address, int posX, int posY) {
    GameMenu *newNode = (GameMenu *) malloc(sizeof(GameMenu));

    newNode -> textureData = loadTexture(Address);
    newNode -> options.w = newNode -> textureData -> width;
    newNode -> options.h = newNode -> textureData -> height;
    newNode -> options.x = posX - (newNode -> options.w / 2);
    newNode -> options.y = posY;
    newNode -> next = NULL;

    if (menuHead == NULL) {
        menuHead = newNode;
        lastMenuOption = newNode;
        return;
    }
    lastMenuOption -> next = newNode;
    lastMenuOption = newNode;
}

extern SDL_Renderer *Render;

int menuInit() { // loading images !! as our texts are image !
    int widthCenter = Width / 2;
    int heightTop = Height / 12;
    createMenuNode("../images/menu/pressEnter.png", widthCenter, 1 * heightTop);
    createMenuNode("../images/menu/onePlayer.png", widthCenter, 3 * heightTop);
    createMenuNode("../images/menu/twoPlayer.png", widthCenter, 4 * heightTop);
    createMenuNode("../images/menu/records.png", widthCenter, 5 * heightTop);
    createMenuNode("../images/menu/leaderBoard.png", widthCenter, 6 * heightTop);
    createMenuNode("../images/menu/settings.png", widthCenter, 7 * heightTop);
    createMenuNode("../images/menu/quit.png", widthCenter, 8 * heightTop);

    extern int SettingsMenuInit();
    SettingsMenuInit();
    return 0;
}



extern int selectedMenuOption;
void renderMenu() {
    GameMenu *head = menuHead;
    int count = -1; // first node in our link list is not selectable ( it's header ) !!
    while (head != NULL) {
        if (count == selectedMenuOption)
            SDL_SetTextureColorMod( head -> textureData -> texture, 255, 200, 20 );
        else
            SDL_SetTextureColorMod( head -> textureData -> texture, 255, 255, 255 );

        SDL_RenderCopy(Render, head -> textureData -> texture, NULL, &(head -> options));
        head = head -> next;
        count++;
    }
    playMenuMusic();
}

void menuUpdate(int state) {
    playClickSoundEffect();
    if (state > 0) {
        if (selectedMenuOption == QuitGame)
            selectedMenuOption = onePlayer;
        else
            selectedMenuOption++;
    } else {
        if (selectedMenuOption == onePlayer)
            selectedMenuOption = QuitGame;
        else
            selectedMenuOption--;
    }
}
