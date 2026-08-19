#include "Room.h"

#include <iostream>

// Creates Room 1.
Room::Room()
{
    roomNumber = 1;

    interactableCount = 0;

    keypad = nullptr;
    exitDoor = nullptr;

    // Give every pointer a safe value first.
    for (int i = 0; i < 10; i++)
    {
        interactables[i] = nullptr;
    }

    // --------------------------------
    // CARD TABLE
    // --------------------------------

    CardTable* cardTable =
        new CardTable(
            16,
            7,
            18,
            5);

    addInteractable(cardTable);

    // --------------------------------
    // KEYPAD
    // --------------------------------

    keypad =
        new KeypadPuzzle(
            39,
            2);

    keypad->setUnlocked(true);

    addInteractable(keypad);

    // --------------------------------
    // EXIT DOOR
    // --------------------------------

    exitDoor =
        new Door(
            39,
            4);

    exitDoor->setUnlocked(false);

    addInteractable(exitDoor);

    // Build Room 1.
    createRoom();
}

// Deletes all objects that Room created.
Room::~Room()
{
    for (int i = 0;
        i < interactableCount;
        i++)
    {
        if (interactables[i] != nullptr)
        {
            // Since Interactable has a
            // virtual destructor, this safely
            // deletes CardTable, KeypadPuzzle,
            // Door, etc.
            delete interactables[i];

            interactables[i] = nullptr;
        }
    }

    // keypad and exitDoor pointed to
    // objects that were already deleted
    // through interactables[].
    //
    // Do NOT delete them again.
    keypad = nullptr;
    exitDoor = nullptr;
}

// Adds an interactable to the room.
void Room::addInteractable(
    Interactable* object)
{
    if (object != nullptr &&
        interactableCount < 10)
    {
        interactables[interactableCount]
            = object;

        interactableCount++;
    }
}

// Clears room UI.
void Room::clearRoom()
{
    for (int y = 0;
        y < HEIGHT;
        y++)
    {
        for (int x = 0;
            x < WIDTH;
            x++)
        {
            roomLayout[y][x] = ' ';
        }
    }
}

// Draws outer walls.
void Room::drawWalls()
{
    // Top and bottom walls.
    for (int x = 0;
        x < WIDTH;
        x++)
    {
        roomLayout[0][x] = '-';

        roomLayout[HEIGHT - 1][x]
            = '-';
    }

    // Left and right walls.
    for (int y = 0;
        y < HEIGHT;
        y++)
    {
        roomLayout[y][0] = '|';

        roomLayout[y][WIDTH - 1]
            = '|';
    }

    // Corners.
    roomLayout[0][0] = '+';

    roomLayout[0][WIDTH - 1]
        = '+';

    roomLayout[HEIGHT - 1][0]
        = '+';

    roomLayout[HEIGHT - 1][WIDTH - 1]
        = '+';
}

// Draws the Card Table.
void Room::drawTable()
{
    int startX = 16;
    int startY = 7;

    // Top and bottom.
    for (int x = startX;
        x <= startX + 17;
        x++)
    {
        roomLayout[startY][x]
            = '-';

        roomLayout[startY + 4][x]
            = '-';
    }

    // Left and right sides.
    for (int y = startY;
        y <= startY + 4;
        y++)
    {
        roomLayout[y][startX]
            = '|';

        roomLayout[y][startX + 17]
            = '|';
    }

    // Corners.
    roomLayout[startY][startX]
        = '+';

    roomLayout[startY][startX + 17]
        = '+';

    roomLayout[startY + 4][startX]
        = '+';

    roomLayout[startY + 4][startX + 17]
        = '+';

    const char tableText[] =
        "CARD TABLE";

    for (int i = 0;
        tableText[i] != '\0';
        i++)
    {
        roomLayout[startY + 2]
            [startX + 4 + i]
            = tableText[i];
    }
}

// Draws keypad.
void Room::drawKeypad()
{
    int startX = 39;
    int startY = 2;

    if (keypad->getUnlocked()
        == false)
    {
        const char text[] =
            "[LOCKED]";

        for (int i = 0;
            text[i] != '\0';
            i++)
        {
            roomLayout[startY]
                [startX + i]
                = text[i];
        }
    }
    else
    {
        const char text[] =
            "[KEYPAD]";

        for (int i = 0;
            text[i] != '\0';
            i++)
        {
            roomLayout[startY]
                [startX + i]
                = text[i];
        }
    }
}

// Draws exit door.
void Room::drawDoor()
{
    int startX = 39;
    int startY = 4;

    if (exitDoor->getUnlocked()
        == false)
    {
        const char text[] =
            "[LOCKED]";

        for (int i = 0;
            text[i] != '\0';
            i++)
        {
            roomLayout[startY]
                [startX + i]
                = text[i];
        }
    }
    else
    {
        const char text[] =
            "[ DOOR ]";

        for (int i = 0;
            text[i] != '\0';
            i++)
        {
            roomLayout[startY]
                [startX + i]
                = text[i];
        }
    }
}

// Draws other furniture.
void Room::drawFurniture()
{
    const char cabinetText[] =
        "[CABINET]";

    const char chairText[] =
        "[CHAIR]";

    // Cabinet.
    for (int i = 0;
        cabinetText[i] != '\0';
        i++)
    {
        roomLayout[14][6 + i]
            = cabinetText[i];
    }

    // Chair.
    for (int i = 0;
        chairText[i] != '\0';
        i++)
    {
        roomLayout[14][35 + i]
            = chairText[i];
    }
}

// Rebuilds complete Room 1.
void Room::createRoom()
{
    clearRoom();

    drawWalls();

    drawTable();

    drawKeypad();

    drawDoor();

    drawFurniture();
}

// Displays Room 1.
void Room::drawRoom(
    int playerX,
    int playerY,
    bool playerSeated)
{
    std::cout << std::endl;

    std::cout
        << "================ ROOM "
        << roomNumber
        << " ================"
        << std::endl;

    std::cout << std::endl;

    for (int y = 0;
        y < HEIGHT;
        y++)
    {
        for (int x = 0;
            x < WIDTH;
            x++)
        {
            // Player is drawn over the room,
            // but isn't stored inside roomLayout.
            if (x == playerX &&
                y == playerY &&
                playerSeated == false)
            {
                std::cout << 'P';
            }
            else
            {
                std::cout
                    << roomLayout[y][x];
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::cout
        << "WASD - Move"
        << std::endl;

    std::cout
        << "E    - Interact"
        << std::endl;

    std::cout << std::endl;
}

// Collision detection.
bool Room::isWalkable(
    int x,
    int y)
{
    // Make sure position is inside room.
    if (x < 0 ||
        x >= WIDTH ||
        y < 0 ||
        y >= HEIGHT)
    {
        return false;
    }

    // Every Interactable blocks movement.
    for (int i = 0;
        i < interactableCount;
        i++)
    {
        if (interactables[i]
            != nullptr)
        {
            if (interactables[i]->
                containsPosition(x, y))
            {
                return false;
            }
        }
    }

    // Empty spaces can be walked on.
    if (roomLayout[y][x] == ' ')
    {
        return true;
    }

    // Walls and furniture block movement.
    return false;
}

// Searches for an Interactable
// at a particular coordinate.
Interactable* Room::getInteractableAt(
    int x,
    int y)
{
    for (int i = 0;
        i < interactableCount;
        i++)
    {
        if (interactables[i]
            != nullptr)
        {
            if (interactables[i]->
                containsPosition(x, y))
            {
                return interactables[i];
            }
        }
    }

    return nullptr;
}

// Returns Room number.
int Room::getRoomNumber()
{
    return roomNumber;
}

// Returns keypad state.
bool Room::getKeypadUnlocked()
{
    return keypad->getUnlocked();
}

// Locks/unlocks keypad.
void Room::setKeypadUnlocked(
    bool unlocked)
{
    keypad->setUnlocked(unlocked);

    // Redraw [LOCKED] / [KEYPAD].
    createRoom();
}

// Returns actual KeypadPuzzle.
KeypadPuzzle* Room::getKeypadPuzzle()
{
    return keypad;
}

// Returns door state.
bool Room::getDoorUnlocked()
{
    return exitDoor->getUnlocked();
}

// Locks/unlocks door.
void Room::setDoorUnlocked(
    bool unlocked)
{
    exitDoor->setUnlocked(unlocked);

    // Redraw [LOCKED] / [ DOOR ].
    createRoom();
}

// Returns actual Door.
Door* Room::getDoor()
{
    return exitDoor;
}