void addNewRecordToLeaderBoardFile(char nickname[21], int score) {
    FILE *leaderBoardFile = fopen("../files/leaderboard.csv", "a+");
    if (leaderBoardFile == NULL) {
        SDL_Log("some thing wen't wrong...");
        return;
    }

    fprintf(leaderBoardFile, "%s , %06d\n", nickname, score);
    fclose(leaderBoardFile);
}

void insertRecordInLeaderBoard(leaderboard **head, leaderboard *node) {
    leaderboard *curr = *head;
    leaderboard *prev = NULL;
    while (curr != NULL) {
        if (curr -> score <= node -> score)
            break;
        prev = curr;
        curr = curr -> next;
    }
    if (prev == NULL) {
        node -> next = curr;
        *head = node;
    } else {
        if (curr != NULL) {
            node -> next = curr;
        }
        prev -> next = node;
    }
}

extern SDL_Texture *loadFromRenderedText();
void getRecordsFromFile(leaderboard **result) {
    FILE *leaderBoardFile = fopen("../files/leaderboard.csv", "r");
    if (leaderBoardFile == NULL) {
        SDL_Log("some thing wen't wrong...");
        return;
    }

    char line[40];
    while (fgets(line, 40, leaderBoardFile)) {
        if (line[0] == '\n' || line[0] == '\0')
            break;
        leaderboard *newNode = (leaderboard *) malloc(sizeof(leaderboard));
        newNode -> next = NULL;
        SDL_Color scoreColor = {255, 255, 255};
        line[strlen(line) - 1] = '\0';
        strcpy(newNode -> nickname, line);
        char score[10];
        sscanf(line, "%*s , %s", score); // puted %*s to ignore first string
        newNode -> score = atoi(score);
        SDL_Log("%d", newNode -> score);
        newNode -> Texture = loadFromRenderedText(line, scoreColor);
        insertRecordInLeaderBoard(result, newNode);
    }
    fclose(leaderBoardFile);

    if (*result == NULL) {
        SDL_Color scoreColor = {255, 50, 50};
        leaderboard *newNode = (leaderboard *) malloc(sizeof(leaderboard));
        newNode -> next = NULL;
        newNode -> Texture = loadFromRenderedText("Not Found", scoreColor);
        insertRecordInLeaderBoard(result, newNode);
    }
}