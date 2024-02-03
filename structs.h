//
// Created by Asus on 1/27/2024.
//

#ifndef FINAL_PROJECT_LAB_STRUCTS_H
#define FINAL_PROJECT_LAB_STRUCTS_H


typedef struct NODE {
    SDL_Texture *texture;
    int width;
    int height;
    struct NODE *next;
} texture;

typedef struct SETTINGNODE {
    texture *textureData;
    int value;
    int type;
    SDL_Rect options;
    struct SETTINGNODE *next;
} SettingsMenu;

typedef struct MENUNODE {
    texture *textureData;
    SDL_Rect options;
    struct MENUNODE *next;
} GameMenu;

typedef struct LEADERBOARD {
    char nickname[40];
    int score;
    SDL_Texture *Texture;
    struct LEADERBOARD *next;
} leaderboard;

#endif //FINAL_PROJECT_LAB_STRUCTS_H
