#include "raylib.h"

#include "star/star.h"
#include "planet/planet.h"

int main(void)
{
    
    const int screenWidth = 1000;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Emil Planetarium");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {

        BeginDrawing();

            ClearBackground(BLACK);

            drawStar(screenWidth, screenHeight);

            createNewPlanet();

            drawPlanet();

        EndDrawing();

    }

    CloseWindow();

    return 0;
}