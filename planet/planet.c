#include "raylib.h"
#include "stdio.h"
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

        /*float totalAxisDistance = sqrt(distanceX * distanceX + distanceY * distanceY);

        float totalDistanceX = sqrt(distanceX * distanceX);

        float totalDistanceY = sqrt(distanceY * distanceY); */

        float velocity = 0.3f / sqrtf(distance);

        planets[i].planetAngle += velocity;

        planets[i].positionPlanet.x = starPosition.x + distance * cos(planets[i].planetAngle);
        planets[i].positionPlanet.y = starPosition.y + distance * sin(planets[i].planetAngle);

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

        planets[planetCount].planetColor = generateRandomColor();

        planets[planetCount].planetAngle = atan2(planets[planetCount].positionPlanet.y - starPosition.y, planets[planetCount].positionPlanet.x - starPosition.x);

        planetCount++;
    }

    return 0;
}