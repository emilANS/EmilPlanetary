#include "raylib.h"

#include "star/star.h"
#include "planet/planet.h"
#include "utils/utils.h"

Camera2D camera = {0};

int main(void)
{

    camera.zoom = 1.0f;

    const int screenWidth = 1000;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Emil Planetarium");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera);
        
        drawStar(screenWidth, screenHeight);
        
        createNewPlanet();
        
        drawPlanet();
        
        zoom();

        moveCamera();

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}