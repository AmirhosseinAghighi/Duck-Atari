extern SDL_Renderer *Render;

extern texture *TextureList;

texture *createNewTexture(SDL_Texture *newTexture, int width, int height) {
    texture *textureNode = (texture *) malloc(sizeof(texture));
    if (textureNode == NULL) {
        return NULL;
    }
    textureNode -> texture = newTexture;
    textureNode -> next = NULL;
    textureNode -> width = width;
    textureNode -> height = height;
    return textureNode;
}

texture *insertTextureInList(SDL_Texture *newTexture, int width, int height) {
    if (TextureList == NULL) {
        TextureList = createNewTexture(newTexture, width, height);
        return TextureList;
    }

    texture *newTextureNode = createNewTexture(newTexture, width, height);
    texture *head = TextureList;
    while (head -> next != NULL)
        head = head -> next;

    head -> next = newTextureNode;

    return newTextureNode;
}

// create delete texture by node pointer !!
int deleteTexture(texture *node) {
    texture *head = TextureList;
    texture *prev = NULL;
    while (head != NULL) {
        if (head == node)
            break;
        prev = head;
        head = head -> next;
    }

    if (head == NULL)
        return -1;

    if (prev == NULL) {
        TextureList = head;
    } else {
        prev -> next = head -> next;
    }

    SDL_DestroyTexture(head -> texture);
    free(head);

    return 0;
}

int freeTextures() {
    texture *head = TextureList;
    while (head != NULL) {
        texture *temp = head;
        head = head -> next;
        SDL_DestroyTexture(temp -> texture);
        free(temp);
    }
    TextureList = NULL;
}

texture *loadTexture(char Address[]) {
    SDL_Surface *loadedSurface = IMG_Load(Address);
    if (loadedSurface == NULL) {
        SDL_Log("There was an Error in loading image! Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(Render, loadedSurface);
    if (newTexture == NULL) {
        SDL_Log("There was an Error in creating texture from Loaded Surface (image) Error: %s\n", SDL_GetError());
        return NULL;
    }
    texture *newTextureNode = insertTextureInList(newTexture, loadedSurface -> w, loadedSurface -> h);

    SDL_FreeSurface(loadedSurface); // we don't need this surface as we created texture from it and we will work with that texture ...

    return newTextureNode;
}

texture *loadTransparentTexture(char Address[]) {
    SDL_Surface *loadedSurface = IMG_Load(Address);
    if (loadedSurface == NULL) {
        SDL_Log("There was an Error in loading image! Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface -> format, 0, 0xFF, 0xFf));

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(Render, loadedSurface);
    if (newTexture == NULL) {
        SDL_Log("There was an Error in creating texture from Loaded Surface (image) Error: %s\n", SDL_GetError());
        return NULL;
    }
    texture *newTextureNode = insertTextureInList(newTexture, loadedSurface -> w, loadedSurface -> h);

    SDL_FreeSurface(loadedSurface); // we don't need this surface as we created texture from it and we will work with that texture ...

    return newTextureNode;
}

//int setBackground(SDL_Texture *newBackground) {
//    extern int Width;
//    extern int Height;
//    SDL_Rect options;
//    options.x = 0;
//    options.y = 0;
//    options.w = Width;
//    options.h = Height;
//    int litScaledResult = SDL_BlitScaled(newBackground, NULL, Surface, &options);
//    if (litScaledResult < 0){
//        SDL_Log("There was an error in SDL_BlitScaled function, ERROR: %s\n", SDL_GetError());
//        return -2;
//    }
//    return 0;
//}