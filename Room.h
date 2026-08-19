#pragma once

// Different objects that the player can interact with.
enum InteractionType
{
    NONE,
    CARD_TABLE,
    KEYPAD,
    EXIT_DOOR
};

class Room
{
private:
    // Size of the room.
    static const int WIDTH = 50;
    static const int HEIGHT = 20;

    // Stores the visual layout.
    char roomLayout[HEIGHT][WIDTH];

    int roomNumber;

    // Room 1 keypad starts locked.
    bool keypadUnlocked;

    // Builds the room.
    void clearRoom();
    void drawWalls();
    void drawTable();
    void drawDoor();
    void drawKeypad();
    void drawFurniture();

public:
    Room();

    // Creates all parts of the room.
    void createRoom();

    // Draws the room and temporarily draws the player
    // at the player's coordinates.
    void drawRoom(int playerX, int playerY, bool playerSeated);

    // Checks whether the player is allowed to move
    // onto a particular position.
    bool isWalkable(int x, int y);

    // Checks what interactable object exists
    // at the given position.
    InteractionType getInteractionAt(int x, int y);

    int getRoomNumber();

    bool getKeypadUnlocked();
    void setKeypadUnlocked(bool unlocked);
};