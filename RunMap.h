#pragma once
#include "MapNode.h"

class Map
{
private:
    // Stores all nodes currently in the map.
    MapNode* nodes[7];

    // Number of nodes currently created.
    int nodeCount;

    // Stores the node the player is currently standing on.
    MapNode* currentNode;

public:
    // Constructor.
    Map();

    // Destructor.
    // Deletes all dynamically created MapNode objects.
    ~Map();

    // Creates a temporary test map.
    void createTestMap();

    // Draws the map in the console.
    void drawMap();

    // Returns the player's current node.
    MapNode* getCurrentNode();

    // Moves the player along the left path.
    void travelLeft();

    // Moves the player along the right path.
    void travelRight();
};
