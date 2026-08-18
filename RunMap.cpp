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
void Map::generateMap()
{
    // The first node is always a Fight.
    // This prevents the player from immediately
    // starting at a Shop or Backpack.
    nodes[0] = new MapNode(FIGHT, 400, 500);

    // Second row.
    nodes[1] = new MapNode(
        mapRNG.generateNodeType(), 300, 400);

    nodes[2] = new MapNode(
        mapRNG.generateNodeType(), 500, 400);

    // Middle node.
    nodes[3] = new MapNode(
        mapRNG.generateNodeType(), 400, 300);

    // Fourth row.
    nodes[4] = new MapNode(
        mapRNG.generateNodeType(), 300, 200);

    nodes[5] = new MapNode(
        mapRNG.generateNodeType(), 500, 200);

    // Final node is always a Fight.
    nodes[6] = new MapNode(FIGHT, 400, 100);

    nodeCount = 7;

    // Connect the first node to both branches.
    nodes[0]->setLeftPath(nodes[1]);
    nodes[0]->setRightPath(nodes[2]);

    // Merge into the middle.
    nodes[1]->setRightPath(nodes[3]);
    nodes[2]->setLeftPath(nodes[3]);

    // Split again.
    nodes[3]->setLeftPath(nodes[4]);
    nodes[3]->setRightPath(nodes[5]);

    // Merge into the final Fight.
    nodes[4]->setRightPath(nodes[6]);
    nodes[5]->setLeftPath(nodes[6]);

    // Start at the bottom.
    currentNode = nodes[0];

    currentNode->setVisited(true);
}

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

    std::cout << "Q = Stand Up From Table" << std::endl;
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
