#include "raylib.h"

#include "math.h"

#include "stdio.h"

#include "utils.h"

float calculateDistancePlanetStar(float planetX, float planetY, float starX, float starY)
{

    float distanceBetween;

    distanceBetween = sqrtf((planetX - starX) * (planetX - starX) + (planetY - starY) * (planetY - starY));

    return distanceBetween;
}