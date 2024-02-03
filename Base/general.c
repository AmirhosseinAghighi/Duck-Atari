int randomNumber(int x, int n) {
    int randomNumber = rand() % (n - x + 1) + x;
    return randomNumber;
}