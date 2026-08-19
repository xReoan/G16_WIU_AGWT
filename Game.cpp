#include "Game.h"

#include <iostream>
#include <conio.h>
#include <Windows.h>

// Creates the game.
Game::Game()
{
    // Player begins exploring the room.
    currentState = ROOM_STATE;

    // Clear the screen before the first frame.
    screenNeedsClear = true;

    // Generate the branching map once
    // when the game begins.
    map.generateMap();
}

// Moves the console cursor back to coordinate (0, 0).
//
// This means the new frame overwrites the previous frame
// rather than appearing underneath it.
void Game::moveCursorToTop()
{
    HANDLE consoleHandle =
        GetStdHandle(STD_OUTPUT_HANDLE);

    COORD cursorPosition;

    cursorPosition.X = 0;
    cursorPosition.Y = 0;

    SetConsoleCursorPosition(
        consoleHandle,
        cursorPosition);
}

// Completely clears everything currently
// shown in the console.
void Game::clearScreen()
{
    HANDLE consoleHandle =
        GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screenInfo;

    GetConsoleScreenBufferInfo(
        consoleHandle,
        &screenInfo);

    DWORD consoleSize =
        screenInfo.dwSize.X *
        screenInfo.dwSize.Y;

    DWORD charactersWritten;

    COORD topLeft;

    topLeft.X = 0;
    topLeft.Y = 0;

    // Replace everything currently displayed
    // with blank spaces.
    FillConsoleOutputCharacter(
        consoleHandle,
        ' ',
        consoleSize,
        topLeft,
        &charactersWritten);

    // Reset the console formatting.
    FillConsoleOutputAttribute(
        consoleHandle,
        screenInfo.wAttributes,
        consoleSize,
        topLeft,
        &charactersWritten);

    // Return cursor to the top-left.
    SetConsoleCursorPosition(
        consoleHandle,
        topLeft);
}

// Main game loop.
void Game::run()
{
    while (true)
    {
        // Completely clear only when changing screens.
        if (screenNeedsClear == true)
        {
            clearScreen();

            screenNeedsClear = false;
        }
        else
        {
            // During normal movement, just return
            // to the top-left.
            //
            // This gives much smoother movement
            // than clearing the entire console.
            moveCursorToTop();
        }

        // Draw the current screen.
        draw();

        // Read one key immediately.
        char input = _getch();

        // Let the current state decide
        // what the key does.
        handleInput(input);
    }
}

// Draws whichever UI belongs
// to the current GameState.
void Game::draw()
{
    if (currentState == ROOM_STATE)
    {
        room.drawRoom(
            player.getX(),
            player.getY(),
            false);
    }

    else if (currentState == MAP_STATE)
    {
        map.drawMap();

        std::cout << std::endl;

        std::cout << "A - Take Left Path"
            << std::endl;

        std::cout << "D - Take Right Path"
            << std::endl;

        std::cout << "Q - Stand Up"
            << std::endl;
    }

    else if (currentState == CARD_BATTLE_STATE)
    {
        std::cout
            << "================ CARD BATTLE ================"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Card Battle UI will go here."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Q - Leave Battle"
            << std::endl;
    }
}

// Sends controls to the correct state.
void Game::handleInput(char input)
{
    if (currentState == ROOM_STATE)
    {
        handleRoomInput(input);
    }

    else if (currentState == MAP_STATE)
    {
        handleMapInput(input);
    }

    else if (currentState == CARD_BATTLE_STATE)
    {
        // Temporary testing control.
        if (input == 'Q' || input == 'q')
        {
            currentState = MAP_STATE;

            screenNeedsClear = true;
        }
    }
}

// Handles controls while exploring the room.
void Game::handleRoomInput(char input)
{
    // WASD movement.
    if (input == 'W' || input == 'w' ||
        input == 'A' || input == 'a' ||
        input == 'S' || input == 's' ||
        input == 'D' || input == 'd')
    {
        player.move(input, &room);
    }

    // E = Interact.
    else if (input == 'E' || input == 'e')
    {
        InteractionType interaction =
            getPlayerInteraction();

        // CARD TABLE
        if (interaction == CARD_TABLE)
        {
            std::cout << std::endl;

            std::cout
                << "Are you sure you want to sit down? [Y/N] ";

            char choice = _getch();

            if (choice == 'Y' || choice == 'y')
            {
                // Switch from Room UI
                // to the branching Map UI.
                currentState = MAP_STATE;

                // Completely clear the old Room UI
                // before displaying the map.
                screenNeedsClear = true;
            }
            else
            {
                screenNeedsClear = true;
            }
        }

        // KEYPAD
        else if (interaction == KEYPAD)
        {
            std::cout << std::endl;

            if (room.getKeypadUnlocked() == true)
            {
                std::cout
                    << "The keypad is active."
                    << std::endl;

                // Keypad puzzle state will go here later.
            }
            else
            {
                std::cout
                    << "The keypad has no power."
                    << std::endl;
            }

            _getch();

            screenNeedsClear = true;
        }

        // EXIT DOOR
        else if (interaction == EXIT_DOOR)
        {
            std::cout << std::endl;

            std::cout
                << "The door is locked."
                << std::endl;

            _getch();

            screenNeedsClear = true;
        }
    }
}

// Finds which object is directly
// in front of the player.
InteractionType Game::getPlayerInteraction()
{
    int interactionX = player.getX();
    int interactionY = player.getY();

    char direction =
        player.getFacingDirection();

    // Position directly above player.
    if (direction == 'W')
    {
        interactionY = interactionY - 1;
    }

    // Position directly below player.
    else if (direction == 'S')
    {
        interactionY = interactionY + 1;
    }

    // Position directly left of player.
    else if (direction == 'A')
    {
        interactionX = interactionX - 1;
    }

    // Position directly right of player.
    else if (direction == 'D')
    {
        interactionX = interactionX + 1;
    }

    return room.getInteractionAt(
        interactionX,
        interactionY);
}

// Handles controls while sitting at the table
// and viewing the branching map.
void Game::handleMapInput(char input)
{
    // Take left branch.
    if (input == 'A' || input == 'a')
    {
        map.travelLeft();

        screenNeedsClear = true;
    }

    // Take right branch.
    else if (input == 'D' || input == 'd')
    {
        map.travelRight();

        screenNeedsClear = true;
    }

    // Stand up from the table.
    else if (input == 'Q' || input == 'q')
    {
        std::cout << std::endl;

        std::cout
            << "Are you sure you want to stand up? [Y/N] ";

        char choice = _getch();

        if (choice == 'Y' || choice == 'y')
        {
            // Return to room exploration.
            currentState = ROOM_STATE;
        }

        screenNeedsClear = true;
    }
}