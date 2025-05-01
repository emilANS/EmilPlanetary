#ifndef PLANET_H
#define PLANET_H


#include "raylib.h"

extern int planetCount;

typedef struct Planet
{
    Vector2 positionPlanet;
    
    Vector2 initialPosition;
    
    Color planetColor;
    
    float radiusPlanet;

    float distancePlanetStar;
    
    float planetAngle;
    
    float randomVelocityAndTrajectory;
    
    int actualTrajectoryIndex;
    
    Vector2 trajectoryPositions[150];
} Planet;
#define MAX_PLANETS 50

extern Planet planets[MAX_PLANETS];

int drawPlanet(void);

int createNewPlanet(void);

#endif