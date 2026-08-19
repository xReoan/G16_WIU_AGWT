#pragma once

#include "Room.h"

class Player
{
private:
    // Player's current position inside the room.
    int x;
    int y;

    // Direction the player is currently facing.
    //
    // W = Up
    // A = Left
    // S = Down
    // D = Right
    char facingDirection;

public:
    // Constructor.
    Player();

    // Attempts to move the player one space.
    //
    // The Room checks whether the destination
    // can actually be walked on.
    void move(char direction, Room* room);

    // Getter functions.
    int getX();
    int getY();

    char getFacingDirection();
};