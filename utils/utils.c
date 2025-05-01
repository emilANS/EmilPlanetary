#include "raylib.h"

#include "raymath.h"

#include "math.h"

#include "stdio.h"

#include "utils.h"

#include "../main.h"

float calculateDistancePlanetStar(float planetX, float planetY, float starX, float starY)
{

    float distanceBetween;

    distanceBetween = sqrtf((planetX - starX) * (planetX - starX) + (planetY - starY) * (planetY - starY));

    return distanceBetween;
}

float targetZoom = 1.0f;

int zoom(void)
{

    float wheel = GetMouseWheelMove();

    if (wheel != 0)
    {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        camera.offset = GetMousePosition();

        camera.target = mouseWorldPos;

        float scale = 0.2f * wheel;

        targetZoom = Clamp(expf(logf(camera.zoom) + scale), 0.125f, 64.0f);

        /* camera.zoom = Clamp(expf(logf(camera.zoom) + scale), 0.125f, 64.0f); */
    }

    float smoothSpeed = 0.1f;
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
