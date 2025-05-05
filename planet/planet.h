#ifndef PLANET_H
#define PLANET_H
#define MAX_PLANETS 50

#include "raylib.h"

extern int planetCount;


typedef struct Planet
{
    Vector2 positionPlanet;

    Vector2 initialPosition;

    Color planetColor;

    float radiusPlanet;

    int planetMass;

    float distancePlanetStar;

    float planetAngle;

    float randomVelocityAndTrajectory;

    int actualTrajectoryIndex;

    Vector2 trajectoryPositions[150];

    int planetId;

    float nearPlanetsPosition[MAX_PLANETS];
} Planet;
#define MAX_PLANETS 50

extern Planet planets[MAX_PLANETS];

int drawPlanet(void);

int createNewPlanet(void);

#endif