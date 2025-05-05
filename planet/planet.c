#include "raylib.h"
#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include "math.h"

#include "planet.h"
#include "../star/star.h"

#include "../utils/utils.h"
#include "../main.h"

#define MAX_PLANETS 50

Planet planets[MAX_PLANETS];

int planetCount = 0;

int drawPlanet(void)
{
    for (int i = 0; i < planetCount; i++)
    {

        float planetX = planets[i].positionPlanet.x;
        float planetY = planets[i].positionPlanet.y;

        planets[i].distancePlanetStar = calculateDistancePlanetStar(planetX, planetY, starPosition.x, starPosition.y);

        float distance = planets[i].distancePlanetStar;

        float randomVelocityAndTrajectory = planets[i].randomVelocityAndTrajectory;

        float velocity = randomVelocityAndTrajectory / sqrtf(distance);

        // If the random velocity and trajectory is less than 0.5 rotate the planet orbit in the same way normal clocks spin
        
        // Move the planet through near planets
        for (int pp = 0; pp < planetCount; pp++)
        {
            if (planets[i].planetId != planetCount)
            {
                planets[i].nearPlanetsPosition[pp] = calculateDistancePlanetStar(planetX, planetY, planets[pp].positionPlanet.x, planets[pp].positionPlanet.y);
            }
        }
        
        // This is the id of the planet inside the array of the positions near planets that will be processed
        int planetPositionIdComparison = 0;
        
        // If the position of the planet is the same of the position of the planet sum by one the planetPositionIdComparison
        if (planets[i].nearPlanetsPosition[planetPositionIdComparison] == 0.0)
        {
            planetPositionIdComparison++;
        }
        
        float min = planets[i].nearPlanetsPosition[planetPositionIdComparison];
        
        int nearPlanetId = 0;
        
        for (int t = 0; t < planetCount; t++)
        {
            if (planets[i].nearPlanetsPosition[t] < min && planets[t].planetId != planets[i].planetId)
            {
                min = planets[i].nearPlanetsPosition[t];
                
                nearPlanetId = planets[t].planetId;
            }
        }
        
        distance = planets[i].nearPlanetsPosition[nearPlanetId];
        
        planets[i].planetAngle = atan2(planetY - planets[nearPlanetId].positionPlanet.y, planetX - planets[nearPlanetId].positionPlanet.x);
        
        if (randomVelocityAndTrajectory <= 0.2)
        {
            planets[i].planetAngle += velocity;
        }
        // if not make it spin the other way
        else
        {
            planets[i].planetAngle -= velocity;
        }
        
        // Move the planet around the star
        for (int tr = 0; tr < planetCount; tr++)
        {
            planets[i].positionPlanet.x = planets[nearPlanetId].positionPlanet.x + distance * cos(planets[i].planetAngle);
            planets[i].positionPlanet.y = planets[nearPlanetId].positionPlanet.y + distance * sin(planets[i].planetAngle);
        }
        
        if (planets[i].actualTrajectoryIndex < 150)
        {
            planets[i].trajectoryPositions[planets[i].actualTrajectoryIndex] = (Vector2){planets[i].positionPlanet.x, planets[i].positionPlanet.y};
            
            planets[i].actualTrajectoryIndex++;
            
            for (int tr = 0; tr < sizeof(planets[i].trajectoryPositions) / sizeof(planets[i].trajectoryPositions[0]); tr++)
            {
                DrawPixel(planets[i].trajectoryPositions[tr].x, planets[i].trajectoryPositions[tr].y, planets[i].planetColor);
            }
        }
        else
        {
            planets[i].actualTrajectoryIndex = 0;

            for (int tr = 0; tr < sizeof(planets[i].trajectoryPositions) / sizeof(planets[i].trajectoryPositions[0]); tr++)
            {
                DrawPixel(planets[i].trajectoryPositions[tr].x, planets[i].trajectoryPositions[tr].y, planets[i].planetColor);
            }
        }

        DrawCircle(planets[i].positionPlanet.x, planets[i].positionPlanet.y, planets[i].radiusPlanet, planets[i].planetColor);
    }

    return 0;
}

Color generateRandomColor()
{
    return (Color){
        GetRandomValue(0, 255), // Red
        GetRandomValue(0, 255), // Green
        GetRandomValue(0, 255), // Blue
        255};
}

int createNewPlanet(void)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && planetCount < MAX_PLANETS)
    {
        planets[planetCount].positionPlanet = GetScreenToWorld2D(GetMousePosition(), camera);

        planets[planetCount].distancePlanetStar = calculateDistancePlanetStar(planets[planetCount].positionPlanet.x, planets[planetCount].positionPlanet.y, starPosition.x, starPosition.y);

        if (planets[planetCount].distancePlanetStar < 70)
        {
            return 0;
        }

        srand(time(NULL) + clock());

        float randomNumberVelocity = 0.1f + ((float)rand() / RAND_MAX) * (0.3f - 0.1f);

        float randomNumberPlanetMass = 1 + ((float)rand() / RAND_MAX) * (5 - 1);

        planets[planetCount].planetMass = randomNumberPlanetMass;

        planets[planetCount].randomVelocityAndTrajectory = randomNumberVelocity;

        planets[planetCount].planetColor = generateRandomColor();

        planets[planetCount].planetAngle = atan2(planets[planetCount].positionPlanet.y - starPosition.y, planets[planetCount].positionPlanet.x - starPosition.x);

        planets[planetCount].radiusPlanet = 15.0f;

        planets[planetCount].planetId = planetCount;

        planetCount++;
    }

    return 0;
}
