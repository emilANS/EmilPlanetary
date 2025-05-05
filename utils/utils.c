#include "raylib.h"

#include "raymath.h"

#include "math.h"

#include "stdio.h"

#include "utils.h"

#include "../main.h"
#include "../star/star.h"
#include "../planet/planet.h"

float calculateDistancePlanetStar(float planetX, float planetY, float starX, float starY)
{
    float distanceBetween;

    distanceBetween = sqrtf((planetX - starX) * (planetX - starX) + (planetY - starY) * (planetY - starY));

    return distanceBetween;
}

float targetZoom = 1.0f;

Vector2 targetTransition;

bool userFocusInPlanet = false;

int indexOfFocusedPlanet;

float smoothSpeed = 0.1f;

int zoom(void)
{

    float wheel = GetMouseWheelMove();

    if (wheel != 0)
    {
        float scale = 0.2f * wheel;

        if (userFocusInPlanet == true)
        {
            targetZoom = Clamp(expf(logf(camera.zoom) + scale), 1.0f, 64.0f);
        }
        else
        {
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

            camera.offset = GetMousePosition();

            camera.target = mouseWorldPos;

            targetZoom = Clamp(expf(logf(camera.zoom) + scale), 0.125f, 64.0f);
        }
    }

    camera.zoom = camera.zoom + (targetZoom - camera.zoom) * smoothSpeed;

    return 0;
}

int moveCamera(void)
{
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }

    return 0;
}

int focusCameraOnPlanet(void)
{
    Vector2 mouseWorldPosition = GetScreenToWorld2D(GetMousePosition(), camera);

    for (int i = 0; i < planetCount; i++)
    {
        if (CheckCollisionPointCircle(mouseWorldPosition, planets[i].positionPlanet, planets[i].radiusPlanet * 4))
        {
            if (IsKeyPressed(KEY_F))
            {
                userFocusInPlanet = true;

                indexOfFocusedPlanet = i;
            }
        }
    }

    if (IsKeyPressed(KEY_C))
    {
        userFocusInPlanet = false;

        camera.offset = starPosition;

        camera.target = starPosition;
    }

    if (userFocusInPlanet == true)
    {
        targetTransition = planets[indexOfFocusedPlanet].positionPlanet;

        camera.offset = (Vector2){screenWidth / 2, screenHeight / 2};

        camera.target.x += (targetTransition.x - camera.target.x) * smoothSpeed;
        camera.target.y += (targetTransition.y - camera.target.y) * smoothSpeed;
    }

    return 0;
}
