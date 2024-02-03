leaderboard *leaderboardRecords = NULL;
extern int GameStatus;

void openLeaderBoard() {
    getRecordsFromFile(&leaderboardRecords);
    GameStatus = Leaderboard;
}

void renderLeaderBoard() {
//    SDL_Log("Yo");
    leaderboard *curr = leaderboardRecords;
    int i = 0;
    while (curr != NULL) {
        if (i > 6)
            break;
        int nicknameLength = strlen(curr -> nickname);
//        SDL_Rect pos = {Width / 3 - (nicknameLength * 40) - 30, 80 + (150 * i), nicknameLength * 80, 100};
        SDL_Rect pos = {Width / 2 - (nicknameLength * 30), 80 + (150 * i), nicknameLength * 60, 100};
        SDL_RenderCopy(Render, curr -> Texture, NULL, &pos);
//        pos.x = Width - (6 * 80) - 50;
//        pos.w = 6 * 80;
//        SDL_RenderCopy(Render, curr -> scoreTexture, NULL, &pos);
        curr = curr -> next;
        i++;
    }
}

void unloadLeaderBoard() {
    if (leaderboardRecords != NULL) {
        leaderboard *curr = leaderboardRecords;
        leaderboard *prev = NULL;
        while (curr != NULL) {
            leaderboard *temp = curr;
            SDL_DestroyTexture(curr -> Texture);
            curr = curr -> next;
            free(temp);
        }
        leaderboardRecords = NULL;
    }
}