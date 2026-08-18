#include "RunMap.h"
#include <iostream>

int main()
{
    Map* gameMap = new Map();

    gameMap->createTestMap();
    gameMap->drawMap();

    delete gameMap;
    gameMap = nullptr;

    return 0;
}
