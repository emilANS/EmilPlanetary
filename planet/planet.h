#ifndef PLANET_H
#define PLANET_H

#include "raylib.h"

typedef struct Planet
{
    Vector2 positionPlanet;

    Vector2 initialPosition;

    Color planetColor;

    float distancePlanetStar;

    float planetAngle;

    float randomVelocityAndTrajectory;

    int actualTrajectoryIndex;
    
    Vector2 trajectoryPositions[200];
} Planet;

int drawPlanet(void);

int createNewPlanet(void);

#endif