#include "Room.h"
#include <iostream>

Room::Room()
{
    roomNumber = 1;

    // Defeating the Room 1 boss will change this later.
    keypadUnlocked = false;

    createRoom();
}

// Fills the room with empty spaces.
void Room::clearRoom()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            roomLayout[y][x] = ' ';
        }
    }
}

// Draws the outside walls.
void Room::drawWalls()
{
    // Top and bottom walls.
    for (int x = 0; x < WIDTH; x++)
    {
        roomLayout[0][x] = '-';
        roomLayout[HEIGHT - 1][x] = '-';
    }

    // Left and right walls.
    for (int y = 0; y < HEIGHT; y++)
    {
        roomLayout[y][0] = '|';
        roomLayout[y][WIDTH - 1] = '|';
    }

    // Corners.
    roomLayout[0][0] = '+';
    roomLayout[0][WIDTH - 1] = '+';

    roomLayout[HEIGHT - 1][0] = '+';
    roomLayout[HEIGHT - 1][WIDTH - 1] = '+';
}

// Draws the card table.
void Room::drawTable()
{
    int startX = 16;
    int startY = 7;

    // Top and bottom.
    for (int x = startX; x <= startX + 17; x++)
    {
        roomLayout[startY][x] = '-';
        roomLayout[startY + 4][x] = '-';
    }

    // Left and right.
    for (int y = startY; y <= startY + 4; y++)
    {
        roomLayout[y][startX] = '|';
        roomLayout[y][startX + 17] = '|';
    }

    // Corners.
    roomLayout[startY][startX] = '+';
    roomLayout[startY][startX + 17] = '+';

    roomLayout[startY + 4][startX] = '+';
    roomLayout[startY + 4][startX + 17] = '+';

    const char tableText[] = "CARD TABLE";

    for (int i = 0; tableText[i] != '\0'; i++)
    {
        roomLayout[startY + 2][startX + 4 + i] = tableText[i];
    }
}

// Draws the exit door.
void Room::drawDoor()
{
    const char doorText[] = "[ DOOR ]";

    int startX = 39;
    int startY = 4;

    for (int i = 0; doorText[i] != '\0'; i++)
    {
        roomLayout[startY][startX + i] = doorText[i];
    }
}

// Draws the keypad.
void Room::drawKeypad()
{
    int startX = 39;
    int startY = 2;

    if (keypadUnlocked == false)
    {
        const char text[] = "[LOCKED]";

        for (int i = 0; text[i] != '\0'; i++)
        {
            roomLayout[startY][startX + i] = text[i];
        }
    }
    else
    {
        const char text[] = "[KEYPAD]";

        for (int i = 0; text[i] != '\0'; i++)
        {
            roomLayout[startY][startX + i] = text[i];
        }
    }
}

// Draws non-interactable furniture.
void Room::drawFurniture()
{
    const char cabinetText[] = "[CABINET]";
    const char chairText[] = "[CHAIR]";

    for (int i = 0; cabinetText[i] != '\0'; i++)
    {
        roomLayout[14][6 + i] = cabinetText[i];
    }

    for (int i = 0; chairText[i] != '\0'; i++)
    {
        roomLayout[14][35 + i] = chairText[i];
    }
}

// Builds the complete room.
void Room::createRoom()
{
    clearRoom();

    drawWalls();
    drawTable();
    drawDoor();
    drawKeypad();
    drawFurniture();
}

// Displays the room.
void Room::drawRoom(int playerX, int playerY, bool playerSeated)
{
    std::cout << std::endl;

    std::cout << "================ ROOM "
        << roomNumber
        << " ================"
        << std::endl;

    std::cout << std::endl;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // The player is drawn over the room temporarily.
            // We do NOT store the player inside roomLayout.
            if (x == playerX &&
                y == playerY &&
                playerSeated == false)
            {
                std::cout << 'P';
            }
            else
            {
                std::cout << roomLayout[y][x];
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    if (playerSeated == false)
    {
        std::cout << "WASD - Move" << std::endl;
        std::cout << "E    - Interact" << std::endl;
    }
    else
    {
        std::cout << "You are seated at the Card Table."
            << std::endl;

        std::cout << "Q    - Stand Up" << std::endl;
    }

    std::cout << std::endl;
}

// Collision detection.
//
// The player can only walk onto an empty space.
// Walls, furniture, the table, door and keypad
// contain characters and therefore block movement.
bool Room::isWalkable(int x, int y)
{
    // Make sure the coordinate is inside the room.
    if (x < 0 || x >= WIDTH ||
        y < 0 || y >= HEIGHT)
    {
        return false;
    }

    // Empty spaces can be walked on.
    if (roomLayout[y][x] == ' ')
    {
        return true;
    }

    return false;
}

// Determines which object exists at a position.
InteractionType Room::getInteractionAt(int x, int y)
{
    // CARD TABLE
    //
    // Table occupies:
    // x = 16 to 33
    // y = 7 to 11
    if (x >= 16 && x <= 33 &&
        y >= 7 && y <= 11)
    {
        return CARD_TABLE;
    }

    // KEYPAD
    //
    // Keypad occupies:
    // x = 39 to 46
    // y = 2
    if (x >= 39 && x <= 46 &&
        y == 2)
    {
        return KEYPAD;
    }

    // EXIT DOOR
    //
    // Door occupies:
    // x = 39 to 46
    // y = 4
    if (x >= 39 && x <= 46 &&
        y == 4)
    {
        return EXIT_DOOR;
    }

    return NONE;
}

int Room::getRoomNumber()
{
    return roomNumber;
}

bool Room::getKeypadUnlocked()
{
    return keypadUnlocked;
}

// Later:
//
// boss defeated
//      ↓
// room.setKeypadUnlocked(true);
void Room::setKeypadUnlocked(bool unlocked)
{
    keypadUnlocked = unlocked;

    // Rebuild the room so [LOCKED]
    // changes into [KEYPAD].
    createRoom();
}