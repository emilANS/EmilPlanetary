#include "raylib.h"
#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include "math.h"

#include "planet.h"
#include "../star/star.h"

#include "../utils/utils.h"

#define MAX_PLANETS 50

#define M_PI 3.14159265358979323846

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

        /*float totalAxisDistance = sqrt(distanceX * distanceX + distanceY * distanceY);

        float totalDistanceX = sqrt(distanceX * distanceX);

        float totalDistanceY = sqrt(distanceY * distanceY); */

        float velocity = randomVelocityAndTrajectory / sqrtf(distance);

        // If the random velocity and trajectory is less than 0.5 rotate the planet orbit in the same way normal clocks spin
        if (randomVelocityAndTrajectory <= 0.5)
        {
            planets[i].planetAngle += velocity;
        }
        // if not make it spin the other way
        else
        {
            planets[i].planetAngle -= velocity;
        }

        planets[i].positionPlanet.x = starPosition.x + distance * cos(planets[i].planetAngle);
        planets[i].positionPlanet.y = starPosition.y + distance * sin(planets[i].planetAngle);

        if (planets[i].actualTrajectoryIndex < 200)
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

        DrawCircle(planets[i].positionPlanet.x, planets[i].positionPlanet.y, 15.0f, planets[i].planetColor);
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
        planets[planetCount].positionPlanet = GetMousePosition();

        planets[planetCount].distancePlanetStar = calculateDistancePlanetStar(planets[planetCount].positionPlanet.x, planets[planetCount].positionPlanet.y, starPosition.x, starPosition.y);

        if (planets[planetCount].distancePlanetStar < 70)
        {
            return 0;
        }
        srand(time(NULL) + clock());

        float randomNumber = 0.3f + ((float)rand() / RAND_MAX) * (0.7f - 0.3f);

        planets[planetCount].randomVelocityAndTrajectory = randomNumber;

        planets[planetCount].planetColor = generateRandomColor();

        planets[planetCount].planetAngle = atan2(planets[planetCount].positionPlanet.y - starPosition.y, planets[planetCount].positionPlanet.x - starPosition.x);

        planetCount++;
    }

    return 0;
}