//
// Created by Asus on 1/27/2024.
//

#ifndef FINAL_PROJECT_LAB_ENUMSS_H
#define FINAL_PROJECT_LAB_ENUMSS_H

enum Status {
    Loading,
    Menu,
    SettingsMenuPage,
    preGame,
    Game,
    Leaderboard,
    PauseMenu,
    Gameover,
    Quit
};


enum settingsMenuOptions {
    musicSetting,
    soundEffectSetting,
    levelSetting,
    back
};

enum settingOnOrOff {
    on,
    off
};

enum settingDifficulity {
    easy,
    normal,
    hard,
    mortal
};

enum settingType {
    onOrOff,
    Levels,
    NoneSetting
};

enum keyReturns {
    None,
    GameQuit
};

enum menuStatus {
    onePlayer,
    twoPlayer,
    Records,
    LeaderBoard,
    Settings,
    QuitGame
};


#endif //FINAL_PROJECT_LAB_ENUMSS_H
