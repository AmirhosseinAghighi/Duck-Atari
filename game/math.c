#include <math.h>

double calculateDistance(int x1, int y1, int x2, int y2) {
//    SDL_Log("%d %d %d %d %lf", x1, x1, x2, y2, sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}
