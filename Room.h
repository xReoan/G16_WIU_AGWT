#pragma once

#include "Interactable.h"
#include "CardTable.h"
#include "Puzzle.h"
#include "KeypadPuzzle.h"
#include "Door.h"

class Room
{
private:
    static const int WIDTH = 50;
    static const int HEIGHT = 20;

    char roomLayout[HEIGHT][WIDTH];

    int roomNumber;

    // All interactable objects in the room.
    Interactable* interactables[10];

    int interactableCount;

    // Direct pointers to important Room 1 objects.
    KeypadPuzzle* keypad;
    Door* exitDoor;

    // Adds an interactable to the room.
    void addInteractable(Interactable* object);

    // Room drawing functions.
    void clearRoom();
    void drawWalls();
    void drawTable();
    void drawDoor();
    void drawKeypad();
    void drawFurniture();

public:
    Room();
    ~Room();

    void createRoom();

    void drawRoom(
        int playerX,
        int playerY,
        bool playerSeated);

    // Collision detection.
    bool isWalkable(int x, int y);

    // Interaction detection.
    Interactable* getInteractableAt(
        int x,
        int y);

    int getRoomNumber();

    // Keypad.
    bool getKeypadUnlocked();
    void setKeypadUnlocked(bool unlocked);

    KeypadPuzzle* getKeypadPuzzle();

    // Door.
    bool getDoorUnlocked();
    void setDoorUnlocked(bool unlocked);

    Door* getDoor();
};