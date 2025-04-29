#include "raylib.h"

#include "star.h"

Vector2 starPosition = {0.0, 0.0};

int drawStar(int screenWidth, int screenHeight)
{
    starPosition.x = screenWidth / 2;
    starPosition.y = screenHeight / 2;

    DrawCircle(starPosition.x, starPosition.y, 20.0f, YELLOW);

    return 0;
}