#include "RunMap.h"
#include <iostream>
#include <cstdlib>

int main()
{
    srand(time(0));
    Map* gameMap = new Map();

    gameMap->generateMap();
    gameMap->drawMap();

    delete gameMap;
    gameMap = nullptr;

    return 0;
}
