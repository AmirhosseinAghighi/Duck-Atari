reward * rewardList = NULL;
texture *rewardsTextureByType[4];
extern int checkCollision();

void createNewReward(int x, int y, int type) {
    reward *newReward = (reward *) malloc(sizeof(reward));
    newReward -> data.w = rewardsTextureByType[type] -> width;
    newReward -> data.h = rewardsTextureByType[type] -> height;
    newReward -> data.x = x;
    newReward -> data.y = y;
    newReward -> type = type;
    newReward -> frame = 0;
    newReward -> next = NULL;
    newReward -> changeAmount = 2;

    if  (rewardList == NULL) {
        rewardList = newReward;
    } else {
        newReward -> next = rewardList -> next;
        rewardList -> next = newReward;
    }
}


void generateReward(int x, int y) {
    if (mainSpaceShip -> health == 1) {
        createNewReward(x, y, 1);
    }else if (mainSpaceShip -> fuel <= 200) {
        createNewReward(x, y, 0);
    } else { // now let's check by chance...
        if (randomNumber(1, 100) <= 30) {
            createNewReward(x, y, 1);
        } else if (randomNumber(1, 100) <= 30) {
            createNewReward(x, y, 0);
        } else if (randomNumber(1, 100) <= 20) {
            createNewReward(x, y, 2);
        } else {
            createNewReward(x, y, 3);
        }
    }
}

void deleteReward(reward *curr, reward *prev) {
    if (prev == NULL) {
        rewardList = curr -> next;
    } else {
        prev -> next = curr -> next;
    }
    free(curr);
}

extern void giveSpecialAmoo();
extern void giveShield();
void giveReward(int type) {
    if (type == 0) {
        mainSpaceShip -> fuel += 250;
        if (mainSpaceShip -> fuel > 1000)
            mainSpaceShip -> fuel = 1000;
    } else if (type == 1) {
        if (mainSpaceShip -> health < 5)
            mainSpaceShip -> health += 1;
    } else if (type == 2) {
        giveShield();
    } else if (type == 3) {
        if (mainSpaceShip -> health < 5)
            giveSpecialAmoo();
    }
}

void renderRewards() {
    reward *curr = rewardList;
    reward *prev = NULL;
    while (curr != NULL) {
        SDL_RenderCopy(Render, rewardsTextureByType[curr -> type] -> texture, NULL, &(curr -> data));
        curr -> data.x -= 4;
        if (curr -> frame % 4 == 0) {
            curr -> data.w += curr -> changeAmount;
            curr -> data.y -= curr -> changeAmount / 2;
            curr -> data.h += curr -> changeAmount;
        }
        if (curr -> frame == 20) {
            curr -> changeAmount *= -1;
            curr -> frame = 0;
        }
        curr -> frame++;

        if (checkCollision(&(curr -> data))){
            deleteReward(curr, prev);
            giveReward(curr -> type);
            curr = curr->next;
            continue;
        }


        if (curr -> data.x <= -curr -> data.w) {
            deleteReward(curr, prev);
            curr = curr -> next;
            continue;
        }
        prev = curr;
        curr = curr -> next;
    }
}


void clearRewards() {
    reward *curr = rewardList;
    while (curr != NULL) {
        reward *temp = curr;
        free(temp);
        curr = curr -> next;
    }
    rewardList = NULL;
}