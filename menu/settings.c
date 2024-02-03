// its better to change this later !!
// its storing link list for setting and save the setting node in specefic variable in very bad way !!
// for example we have MusicStatus that hold the first node ( we asign the first node of createSettingMenuNode in it )
// so it's very bad !! as this setting is not going to change a lot, i think it's better to make it without Link list !
// 1/27/2024 - 9:52 PM

// we have another way too !
// we can store the value of setting in specefic variable and pass pointer of that variable to the link list !
// so we will store the pointer of that variable in our link list and we can handle every thing with it in better way !
// we should put a new input in createSettingMenuNode setting to get the variable pointer !!!!
// 1/27//2024 9:55 PM


extern SettingsMenu *MusicStatus;
extern SettingsMenu *SoundEffectStatus;
extern SettingsMenu *LevelStatus;
int selectedDiffLevel = 0;

texture *onOrOffTextures[2];
texture *difficulityLevelsTextures[4];


SettingsMenu *settingsMenuHead = NULL;
SettingsMenu *lastSettingsMenuOption = NULL;
void createSettingMenuNode(char *Address, int posX, int posY, int type) {
    SettingsMenu *newNode = (SettingsMenu *) malloc(sizeof(SettingsMenu));

    newNode -> textureData = loadTexture(Address);
    newNode -> options.w = newNode -> textureData -> width;
    newNode -> options.h = newNode -> textureData -> height;
    if (posX == 0)
        newNode -> options.x = Width / 2 - (newNode -> options.w / 2);
    else
        newNode -> options.x = Width / 2 - newNode -> options.w;
    newNode -> options.y = posY;
    newNode -> next = NULL;
    newNode -> value = 0;
    newNode -> type = type;

    // OMG i didn't think about accessing the setting, its awful !!!
    if (MusicStatus == NULL) {
        SDL_Log("%s\n", Address);
        MusicStatus = newNode;
    } else if (SoundEffectStatus == NULL) {
        SDL_Log("%s\n", Address);
        SoundEffectStatus = newNode;
    } else if (LevelStatus == NULL) {
        LevelStatus = newNode;
    }

    if (settingsMenuHead == NULL) {
        settingsMenuHead = newNode;
        lastSettingsMenuOption = newNode;
        return;
    }
    lastSettingsMenuOption -> next = newNode;
    lastSettingsMenuOption = newNode;
}

extern SDL_Renderer *Render;

int SettingsMenuInit() { // loading images !! as our texts are image !
    int widthCenter = Width / 2;
    int heightTop = Height / 10;
//    createSettingMenuNode("../images/menu/pressEnter.png", 0, 1 * heightTop);
    createSettingMenuNode("../images/menu/Settings/music.png", widthCenter, 3 * heightTop, onOrOff);
    createSettingMenuNode("../images/menu/Settings/soundEffects.png", widthCenter, 4 * heightTop, onOrOff);
    createSettingMenuNode("../images/menu/Settings/difficulity.png", widthCenter, 5 * heightTop, Levels);
    createSettingMenuNode("../images/menu/Settings/back.png", 0, 6 * heightTop, NoneSetting);
    onOrOffTextures[on] = loadTexture("../images/menu/Settings/on.png");
    onOrOffTextures[off] = loadTexture("../images/menu/Settings/off.png");
    difficulityLevelsTextures[easy] = loadTexture("../images/menu/Settings/easy.png");
    difficulityLevelsTextures[normal] = loadTexture("../images/menu/Settings/normal.png");
    difficulityLevelsTextures[hard] = loadTexture("../images/menu/Settings/hard.png");
    difficulityLevelsTextures[mortal] = loadTexture("../images/menu/Settings/mortal.png");
    return 0;
}

int selectedSettingsMenuOption = musicSetting;
void renderSettingsMenu() {
    SettingsMenu *head = settingsMenuHead;
    int count = 0;
    while (head != NULL) {SDL_Rect options;
        texture *selectedOption = NULL;
        if (head -> type == onOrOff) {
            options.w = onOrOffTextures[head -> value] -> width;
            options.h = onOrOffTextures[head -> value] -> height;
            options.x = Width / 2;
            options.y = head -> options.y;
            selectedOption = onOrOffTextures[head -> value];
        }
        if (head -> type == Levels) {
            options.w = difficulityLevelsTextures[head -> value] -> width;
            options.h = difficulityLevelsTextures[head -> value] -> height;
            options.x = Width / 2;
            options.y = head -> options.y;
            selectedOption = difficulityLevelsTextures[head -> value];
        }


        if (count == selectedSettingsMenuOption) {
            SDL_SetTextureColorMod( head -> textureData -> texture, 255, 200, 20 );
            if (selectedOption != NULL)
                SDL_SetTextureColorMod( selectedOption -> texture, 255, 200, 20 );
        } else {
            SDL_SetTextureColorMod( head -> textureData -> texture, 255, 255, 255 );
            if (selectedOption != NULL)
                SDL_SetTextureColorMod( selectedOption -> texture, 255, 255, 255 );
        }

        SDL_RenderCopy(Render, head -> textureData -> texture, NULL, &(head -> options));

        if (selectedOption != NULL)
            SDL_RenderCopy(Render, selectedOption -> texture, NULL, &options);

        head = head -> next;
        count++;
    }
}

void menuSettingsUpdate(int state) {
    playClickSoundEffect();
    if (state > 0) {
        if (selectedSettingsMenuOption == back)
            selectedSettingsMenuOption = musicSetting;
        else
            selectedSettingsMenuOption++;
    } else {
        if (selectedSettingsMenuOption == musicSetting)
            selectedSettingsMenuOption = back;
        else
            selectedSettingsMenuOption--;
    }
}

void toggleOnOrOff(SettingsMenu *curr, int state) {
    if (state > 0) {
        if (curr -> value == 1)
            curr -> value--;
        else
            curr -> value++;
    } else {
        if (curr -> value == 0)
            curr -> value++;
        else
            curr -> value--;
    }

    if (selectedSettingsMenuOption == musicSetting) {
        if (curr -> value == off) {
            stopMusic();
        } else {
            playMenuMusic();
        }
    }
}

void changeDifficulitySetting(SettingsMenu *curr, int state) {
    if (state > 0) {
        if (curr -> value == mortal)
            curr -> value = easy;
        else
            curr -> value++;
    } else {
        if (curr -> value == easy)
            curr -> value = mortal;
        else
            curr -> value--;
    }
    selectedDiffLevel = curr -> value;
}

void settingUpdate(int state) {
    playClickSoundEffect();
    SettingsMenu *curr = settingsMenuHead;
    for (int i = 0; i < selectedSettingsMenuOption; i++, curr = curr -> next);
    if (curr -> type == onOrOff) {
        toggleOnOrOff(curr, state);
    } else if (curr -> type == Levels) {
        changeDifficulitySetting(curr, state);
    }
}