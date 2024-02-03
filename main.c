#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h> // to use Uint32 in timer.c
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define debug 0

//enums
#include "enums.h"

//structs
#include "structs.h"

//dependencies
#include "Base/general.c"
#include "Base/files.c"
#include "Base/texture.c"
#include "Base/text.c"
#include "Base/screen.c"
#include "Base/sounds.c"
#include "Base/startup.c"
#include "Base/background.c"
#include "Base/timer.c"
#include "menu/menu.c"
#include "menu/settings.c"
#include "menu/leaderboard.c"
// game dependencies


#include "game/game_structs.h"
#include "game/base.c"
#include "game/gameMovements.c"
#include "game/gameover.c"


#include "Base/keys.c" // i include this here because we will use Status enum in keys.c

// main variables
SDL_Window *Window = NULL;
SDL_Renderer *Render = NULL;
texture *TextureList = NULL;
SDL_Rect globalRect = {0, 0, 0, 0};
SettingsMenu *MusicStatus = NULL;
SettingsMenu *SoundEffectStatus = NULL;
SettingsMenu *LevelStatus = NULL;
int GameStatus = Menu;
int selectedMenuOption = onePlayer;

int main(int argc, char *argv[])
{
    srand(time(NULL)); // for random numbers ...

    if (init() < 0){
        SDL_Log("There was an error in init %s!!\n", SDL_GetError());
        return -1;
    }

    menuInit();

    menuBackground = loadTexture("../images/space4.png");
    small_Background = loadTexture("../images/small_stars.png");
//    medium_Background = loadTexture("../images/medium_stars.png");

    //game loop
    int quit = 0;
    while( quit == 0 ){
        int changed = 0;
        while(SDL_PollEvent( &e )){
            if( e.type == SDL_QUIT ) {
                quit = 1;
            } else if ( e.type == SDL_KEYDOWN ) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        upOrDownArrowsPressed(-1);
                        break;
                    case SDLK_DOWN:
                        upOrDownArrowsPressed(1);
                        break;
                    case SDLK_LEFT:
                        leftOrRightArrowsPressed(-1);
                        break;
                    case SDLK_RIGHT:
                        leftOrRightArrowsPressed(1);
                        break;

                    case SDLK_SPACE:
                        if ((powerBulletActive == 0 || mainSpaceShip -> specialAmmoAmount <= 0) && e.key.repeat <= 2) {
                            spacePressed();
                        }
                        if (GameStatus == Game && mainSpaceShip -> specialAmmoAmount > 0) {
                            powerBulletActive = SDL_GetTicks();
                        }
                        break;

                    case SDLK_BACKSPACE:
                        if (GameStatus == Gameover && SDL_IsTextInputActive()) {
                            int nicknameLength = strlen(playerNickname);
                            if(nicknameLength > 0)
                            {
                                playerNickname[nicknameLength - 1] = '\0';
                                updatePlayerNickNameTexture();
                            }
                        } else if (GameStatus == Leaderboard) {
                            GameStatus = Menu;
                            unloadLeaderBoard();
                        }
                        break;

                        // general
                    case SDLK_RETURN:
                        switch (GameStatus) {
                            case Menu:
                                switch (selectedMenuOption) {
                                    case QuitGame:
                                        quit = 1;
                                        break;
                                    case onePlayer:
                                        newGame();
                                        GameStatus = preGame;
                                        break;
                                    case Settings:
                                        selectedMenuOption = 0; // first option
                                        GameStatus = SettingsMenuPage;
                                        break;
                                    case LeaderBoard:
                                        selectedMenuOption = 0; // first option
                                        openLeaderBoard();
                                        break;
                                    default:
                                        break;
                                }
                                break;

                            case SettingsMenuPage:
                                if (selectedSettingsMenuOption == back) {
                                    selectedSettingsMenuOption = 0; // first option
                                    GameStatus = Menu;
                                    break;
                                }

                            case Gameover:
                                addNewRecordToLeaderBoardFile(playerNickname, Score);
                                gameOverDone();
                                GameStatus = Menu;
                                break;
                            
                            default:
                                break;
                        }
                        break;
                }
            } else if ( e.type == SDL_TEXTINPUT) {
                if (GameStatus == Gameover && SDL_IsTextInputActive() && strlen(e.text.text) < 20 - strlen(playerNickname)) {
                    if (e.text.text[0] != ' ') {
                        strcat(playerNickname, e.text.text);
                        updatePlayerNickNameTexture();
                    }
                }
            } else if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    if (powerBulletActive != 0 && SDL_GetTicks() - powerBulletActive > 500) {
                        shootPowerBullet();
                    } else {
//                        SDL_Log("realeased !!! %d %d %d", e.key.state, SDL_RELEASED, SDL_PRESSED);
                        powerBulletActive = 0;
                    }
                }
            }
        }


        SDL_RenderClear(Render); // clear the old rendered screen
//        SDL_RenderCopy(Render, menuBackground -> texture, NULL, NULL);
        createBackground(); // create background

        checkKeyStates(); // for game movements and actions ...

        if (GameStatus == Menu)
            renderMenu();

        if (GameStatus == SettingsMenuPage)
            renderSettingsMenu();

        if (GameStatus == preGame)
            renderPreGame();

        if (GameStatus == Game)
            renderOnePlayerGame();

        if (GameStatus == Gameover) {
            renderGameoverGame(); // items will not move ...
            renderGameOverScreen();
        }

        if (GameStatus == Leaderboard)
            renderLeaderBoard();


        SDL_RenderPresent(Render);
    }

    Destroy();

    return 0;
}

