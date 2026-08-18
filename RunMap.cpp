#include "RunMap.h"
#include <iostream>

// Creates an empty map.
Map::Map()
{
    nodeCount = 0;
    currentNode = nullptr;

    // Make sure every pointer starts as nullptr.
    for (int i = 0; i < 7; i++)
    {
        nodes[i] = nullptr;
    }
}

// Deletes all dynamically created nodes.
Map::~Map()
{
    for (int i = 0; i < nodeCount; i++)
    {
        if (nodes[i] != nullptr)
        {
            delete nodes[i];
            nodes[i] = nullptr;
        }
    }
}

// Creates a basic branching test map.
//
//             [F]
//            /   \
//          [S]   [F]
//            \   /
//             [B]
//            /   \
//          [F]   [S]
//            \   /
//           [START]
void Map::createTestMap()
{
    // Bottom node.
    nodes[0] = new MapNode(FIGHT, 400, 500);

    // Second row.
    nodes[1] = new MapNode(FIGHT, 300, 400);
    nodes[2] = new MapNode(SHOP, 500, 400);

    // Middle node.
    nodes[3] = new MapNode(BACKPACK, 400, 300);

    // Fourth row.
    nodes[4] = new MapNode(SHOP, 300, 200);
    nodes[5] = new MapNode(FIGHT, 500, 200);

    // Final node.
    nodes[6] = new MapNode(FIGHT, 400, 100);

    nodeCount = 7;

    // Connect bottom node to the second row.
    nodes[0]->setLeftPath(nodes[1]);
    nodes[0]->setRightPath(nodes[2]);

    // Merge both paths into the middle node.
    nodes[1]->setRightPath(nodes[3]);
    nodes[2]->setLeftPath(nodes[3]);

    // Split again.
    nodes[3]->setLeftPath(nodes[4]);
    nodes[3]->setRightPath(nodes[5]);

    // Merge into the final node.
    nodes[4]->setRightPath(nodes[6]);
    nodes[5]->setLeftPath(nodes[6]);

    // Player begins at the bottom node.
    currentNode = nodes[0];

    currentNode->setVisited(true);
}

// Draws the current test map.
//
// This is hard-coded visually for now.
// Later, the 2D renderer will use each node's x and y position.
void Map::drawMap()
{
    std::cout << std::endl;

    std::cout << "             ["
        << nodes[6]->getSymbol()
        << "]" << std::endl;

    std::cout << "            /   \\" << std::endl;

    std::cout << "          ["
        << nodes[4]->getSymbol()
        << "]   ["
        << nodes[5]->getSymbol()
        << "]" << std::endl;

    std::cout << "            \\   /" << std::endl;

    std::cout << "             ["
        << nodes[3]->getSymbol()
        << "]" << std::endl;

    std::cout << "            /   \\" << std::endl;

    std::cout << "          ["
        << nodes[1]->getSymbol()
        << "]   ["
        << nodes[2]->getSymbol()
        << "]" << std::endl;

    std::cout << "            \\   /" << std::endl;

    std::cout << "            [YOU]" << std::endl;

    std::cout << std::endl;

    std::cout << "F = Fight" << std::endl;
    std::cout << "S = Shop" << std::endl;
    std::cout << "B = Backpack" << std::endl;
}

// Returns the node the player is currently standing on.
MapNode* Map::getCurrentNode()
{
    return currentNode;
}

// Travels along the current node's left path.
void Map::travelLeft()
{
    if (currentNode != nullptr &&
        currentNode->getLeftPath() != nullptr)
    {
        currentNode = currentNode->getLeftPath();

        currentNode->setVisited(true);
    }
}

// Travels along the current node's right path.
void Map::travelRight()
{
    if (currentNode != nullptr &&
        currentNode->getRightPath() != nullptr)
    {
        currentNode = currentNode->getRightPath();

        currentNode->setVisited(true);
    }
}