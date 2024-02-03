//
// Created by Asus on 1/28/2024.
//

#ifndef FINAL_PROJECT_LAB_GAME_STRUCTS_H
#define FINAL_PROJECT_LAB_GAME_STRUCTS_H
    typedef struct spaceShip {
        texture *texture;
        texture *bulletTexture;
        texture *backfire1Texture;
        texture *backfire2Texture;
        texture *backfire3Texture;
        texture *powerModeTexture;
        texture *shieldModeTexture;
        SDL_Rect coords;
        int shooting;
        int Hspeed; // horizontal
        int Vspeed; //vertical
        double health;
        double fuel;
        int shakeFrame;
        int maxShakeFrame;
        int shakeChange;
        SDL_Rect collision[7];
        Uint32 sheildTimer;
        int specialAmmoAmount;
    } spaceShip;


    typedef struct MINE {
        SDL_Rect data;
        Uint32 startTime;
        int active;
        int speed;
        struct MINE *next;
    } mine;

    typedef struct EXPLOSION {
        SDL_Rect data;
        int frame;
        int type;
        struct EXPLOSION *next;
    } explosion;

    typedef struct CARGOSPACESHIP {
        SDL_Rect data;
        double degree;
        int speed;
        int health;
        struct CARGOSPACESHIP *next;
    } cargoSpaceShip;


    typedef struct BULLET {
        SDL_Rect data;
        double degree;
        int speed;
        int type;
        int deleted;
        double a; // math purpose ax + b = y
        double b; // math purpose ax + b = y
        struct BULLET *next;
    } bullet;

    typedef struct REWARD {
        SDL_Rect data;
        int changeAmount;
        int type;
        int frame;
        struct REWARD *next;
    } reward;

    typedef struct BOMBER {
        SDL_Rect data;
        Uint32 lastShotTime;
        int speed;
        int health;
        int direction;
        int ammoAmount;
        int status;
        struct BOMBER *next;
    } bomber;

    typedef struct JET {
        SDL_Rect data;
        Uint32 lastShotTime;
        int speed;
        int health;
        struct JET *next;
    } jet;

    typedef struct DIFLEVEL {
        int mineSpawnChance;
        int maxSpawnedMines;
        int mineSpawnCoolDown;

        int cargoSpawnChance;
        int maxSpawnedCargo;
        int cargoSpawnCooldown;

        int bomberSpawnChance;
        int maxSpawnedBomber;
        int bomberSpawnCoolDown;

        int jetSpawnChance;
        int maxSpawnedJet;
        int jetShootChance;
        int jetSpawnCooldown;
    } difLevel;

#endif //FINAL_PROJECT_LAB_GAME_STRUCTS_H