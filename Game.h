#pragma once

#include "Room.h"
#include "Player.h"
#include "RunMap.h"

// Represents which part of the game
// the player is currently viewing.
enum GameState
{
    ROOM_STATE,
    MAP_STATE,
    CARD_BATTLE_STATE
};

class Game
{
private:
    // Main game objects.
    Room room;
    Player player;
    Map map;

    // Stores the current game state.
    GameState currentState;

    // True when the console should be
    // completely cleared before drawing.
    bool screenNeedsClear;

    // Moves the console cursor back to the top-left.
    //
    // This allows movement to appear in the SAME
    // room instead of printing another room underneath.
    void moveCursorToTop();

    // Completely clears the console.
    //
    // Mainly used when changing between states/screens.
    void clearScreen();

    // Draws whichever UI belongs
    // to the current state.
    void draw();

    // Sends input to the correct state.
    void handleInput(char input);

    // Room controls.
    void handleRoomInput(char input);

    // Branching map controls.
    void handleMapInput(char input);

    // Checks the position directly
    // in front of the player.
    InteractionType getPlayerInteraction();

public:
    // Constructor.
    Game();

    // Runs the main game loop.
    void run();
};