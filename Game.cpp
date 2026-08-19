#include "Game.h"

#include <iostream>
#include <conio.h>
#include <Windows.h>

Game::Game()
{
    currentState = ROOM_STATE;

    activePuzzle = nullptr;

    screenNeedsClear = true;

    map.generateMap();
}

// Moves cursor back to top-left.
void Game::moveCursorToTop()
{
    HANDLE consoleHandle =
        GetStdHandle(
            STD_OUTPUT_HANDLE);

    COORD cursorPosition;

    cursorPosition.X = 0;
    cursorPosition.Y = 0;

    SetConsoleCursorPosition(
        consoleHandle,
        cursorPosition);
}

// Completely clears console.
void Game::clearScreen()
{
    HANDLE consoleHandle =
        GetStdHandle(
            STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO
        screenInfo;

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

    FillConsoleOutputCharacter(
        consoleHandle,
        ' ',
        consoleSize,
        topLeft,
        &charactersWritten);

    FillConsoleOutputAttribute(
        consoleHandle,
        screenInfo.wAttributes,
        consoleSize,
        topLeft,
        &charactersWritten);

    SetConsoleCursorPosition(
        consoleHandle,
        topLeft);
}

// Main loop.
void Game::run()
{
    while (true)
    {
        if (screenNeedsClear == true)
        {
            clearScreen();

            screenNeedsClear = false;
        }
        else
        {
            moveCursorToTop();
        }

        draw();

        char input =
            _getch();

        handleInput(input);
    }
}

// Draws current state.
void Game::draw()
{
    // ==========================
    // ROOM
    // ==========================

    if (currentState == ROOM_STATE)
    {
        room.drawRoom(
            player.getX(),
            player.getY(),
            false);
    }

    // ==========================
    // MAP
    // ==========================

    else if (currentState == MAP_STATE)
    {
        map.drawMap();

        std::cout << std::endl;

        std::cout
            << "A / D - Select Path"
            << std::endl;

        std::cout
            << "E     - Confirm Path"
            << std::endl;

        std::cout
            << "Q     - Stand Up"
            << std::endl;
    }

    // ==========================
    // FIGHT
    // ==========================

    else if (
        currentState ==
        CARD_BATTLE_STATE)
    {
        std::cout
            << "================ CARD BATTLE ================"
            << std::endl;

        std::cout << std::endl;

        if (map.isAtFinalNode() == true)
        {
            std::cout
                << "BOSS BATTLE"
                << std::endl;
        }
        else
        {
            std::cout
                << "Enemy Encounter"
                << std::endl;
        }

        std::cout << std::endl;

        std::cout
            << "Card Battle system will go here."
            << std::endl;

        std::cout << std::endl;

        // Temporary testing control.
        std::cout
            << "E - Win Battle (TEST)"
            << std::endl;
    }

    // ==========================
    // SHOP
    // ==========================

    else if (
        currentState ==
        SHOP_STATE)
    {
        std::cout
            << "================ ITEM SHOP ================"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "A strange merchant waits behind the counter."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Shop system will go here later."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Q - Leave Shop"
            << std::endl;
    }

    // ==========================
    // BACKPACK
    // ==========================

    else if (
        currentState ==
        BACKPACK_STATE)
    {
        std::cout
            << "================ BACKPACK ================"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "You find an abandoned backpack."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Something useful may be inside."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "E - Take Item"
            << std::endl;

        std::cout
            << "Q - Leave"
            << std::endl;
    }

    // ==========================
    // PUZZLE
    // ==========================

    else if (
        currentState ==
        PUZZLE_STATE)
    {
        if (activePuzzle != nullptr)
        {
            // Polymorphism.
            activePuzzle->draw();
        }
    }
}

// Sends input to correct state.
void Game::handleInput(
    char input)
{
    if (currentState == ROOM_STATE)
    {
        handleRoomInput(input);
    }

    else if (currentState == MAP_STATE)
    {
        handleMapInput(input);
    }

    else if (
        currentState ==
        CARD_BATTLE_STATE)
    {
        handleCardBattleInput(input);
    }

    else if (
        currentState ==
        SHOP_STATE)
    {
        handleShopInput(input);
    }

    else if (
        currentState ==
        BACKPACK_STATE)
    {
        handleBackpackInput(input);
    }

    else if (
        currentState ==
        PUZZLE_STATE)
    {
        handlePuzzleInput(input);
    }
}

// Room controls.
void Game::handleRoomInput(
    char input)
{
    // Movement.
    if (input == 'W' ||
        input == 'w' ||
        input == 'A' ||
        input == 'a' ||
        input == 'S' ||
        input == 's' ||
        input == 'D' ||
        input == 'd')
    {
        player.move(
            input,
            &room);
    }

    // Interaction.
    else if (
        input == 'E' ||
        input == 'e')
    {
        Interactable* object =
            getPlayerInteractable();

        if (object != nullptr)
        {
            // POLYMORPHISM.
            InteractionResult result =
                object->interact();

            // Card Table.
            if (result == OPEN_MAP)
            {
                std::cout << std::endl;

                std::cout
                    << "Are you sure you want to sit down? [Y/N] ";

                char choice =
                    _getch();

                if (choice == 'Y' ||
                    choice == 'y')
                {
                    currentState =
                        MAP_STATE;
                }

                screenNeedsClear =
                    true;
            }

            // Puzzle.
            else if (
                result ==
                OPEN_PUZZLE)
            {
                activePuzzle =
                    room.getKeypadPuzzle();

                room.getKeypadPuzzle()->
                    clearEnteredCode();

                activePuzzle->
                    setExitRequested(false);

                currentState =
                    PUZZLE_STATE;

                screenNeedsClear =
                    true;
            }

            // Door.
            else if (
                result ==
                OPEN_DOOR)
            {
                std::cout << std::endl;

                std::cout
                    << "The door opens."
                    << std::endl;

                std::cout
                    << "Room 1 complete!"
                    << std::endl;

                _getch();

                screenNeedsClear =
                    true;
            }

            // Locked object.
            else if (
                result ==
                LOCKED)
            {
                std::cout << std::endl;

                std::cout
                    << "It is currently locked."
                    << std::endl;

                _getch();

                screenNeedsClear =
                    true;
            }
        }
    }
}

// Finds interactable directly
// in front of Player.
Interactable* Game::getPlayerInteractable()
{
    int interactionX =
        player.getX();

    int interactionY =
        player.getY();

    char direction =
        player.getFacingDirection();

    if (direction == 'W')
    {
        interactionY--;
    }

    else if (direction == 'S')
    {
        interactionY++;
    }

    else if (direction == 'A')
    {
        interactionX--;
    }

    else if (direction == 'D')
    {
        interactionX++;
    }

    return room.getInteractableAt(
        interactionX,
        interactionY);
}

// ================================
// MAP CONTROLS
// ================================

void Game::handleMapInput(
    char input)
{
    // A selects left.
    if (input == 'A' ||
        input == 'a')
    {
        map.selectLeft();
    }

    // D selects right.
    else if (
        input == 'D' ||
        input == 'd')
    {
        map.selectRight();
    }

    // E confirms selected path.
    else if (
        input == 'E' ||
        input == 'e')
    {
        // Only continue if a valid
        // path was actually selected.
        if (map.travelSelected() == true)
        {
            activateCurrentMapNode();

            screenNeedsClear =
                true;
        }
    }

    // Q stands up.
    else if (
        input == 'Q' ||
        input == 'q')
    {
        std::cout << std::endl;

        std::cout
            << "Are you sure you want to stand up? [Y/N] ";

        char choice =
            _getch();

        if (choice == 'Y' ||
            choice == 'y')
        {
            currentState =
                ROOM_STATE;
        }

        screenNeedsClear =
            true;
    }
}

// Checks which node the player
// just travelled onto.
void Game::activateCurrentMapNode()
{
    MapNode* node =
        map.getCurrentNode();

    if (node == nullptr)
    {
        return;
    }

    NodeType type =
        node->getType();

    // Fight.
    if (type == FIGHT)
    {
        currentState =
            CARD_BATTLE_STATE;
    }

    // Shop.
    else if (type == SHOP)
    {
        currentState =
            SHOP_STATE;
    }

    // Backpack.
    else if (type == BACKPACK)
    {
        currentState =
            BACKPACK_STATE;
    }
}

// ================================
// CARD BATTLE
// ================================

void Game::handleCardBattleInput(
    char input)
{
    // TEMPORARY:
    //
    // Press E to pretend the player
    // won the battle.
    if (input == 'E' ||
        input == 'e')
    {
        // If this was the final node,
        // treat it as Room 1's boss.
        if (map.isAtFinalNode() == true)
        {
            // Boss defeated!
            room.setKeypadUnlocked(true);

            clearScreen();

            std::cout
                << "================ BOSS DEFEATED ================"
                << std::endl;

            std::cout << std::endl;

            std::cout
                << "The enemy falls."
                << std::endl;

            std::cout << std::endl;

            std::cout
                << "Somewhere behind you..."
                << std::endl;

            std::cout
                << "you remember the code: '9743'"
                << std::endl;

            std::cout << std::endl;

            std::cout
                << "Press any key to continue."
                << std::endl;

            _getch();
        }

        // Return to progression map.
        currentState =
            MAP_STATE;

        screenNeedsClear =
            true;
    }
}

// ================================
// SHOP
// ================================

void Game::handleShopInput(
    char input)
{
    if (input == 'Q' ||
        input == 'q')
    {
        currentState =
            MAP_STATE;

        screenNeedsClear =
            true;
    }
}

// ================================
// BACKPACK
// ================================

void Game::handleBackpackInput(
    char input)
{
    // Temporary item collection.
    if (input == 'E' ||
        input == 'e')
    {
        std::cout << std::endl;

        std::cout
            << "You take the item from the backpack."
            << std::endl;

        std::cout
            << "Inventory system will be added later."
            << std::endl;

        _getch();

        currentState =
            MAP_STATE;

        screenNeedsClear =
            true;
    }

    // Leave without taking item.
    else if (
        input == 'Q' ||
        input == 'q')
    {
        currentState =
            MAP_STATE;

        screenNeedsClear =
            true;
    }
}

// ================================
// PUZZLE
// ================================

void Game::handlePuzzleInput(
    char input)
{
    if (activePuzzle != nullptr)
    {
        activePuzzle->
            handleInput(input);

        // Puzzle solved.
        if (activePuzzle->
            getSolved() == true)
        {
            room.setDoorUnlocked(true);

            clearScreen();

            activePuzzle->draw();

            std::cout << std::endl;

            std::cout
                << "The exit door has been unlocked."
                << std::endl;

            std::cout
                << "Press any key to continue."
                << std::endl;

            _getch();

            currentState =
                ROOM_STATE;

            activePuzzle =
                nullptr;

            screenNeedsClear =
                true;
        }

        // Q pressed.
        else if (
            activePuzzle->
            getExitRequested() == true)
        {
            activePuzzle->
                setExitRequested(false);

            currentState =
                ROOM_STATE;

            activePuzzle =
                nullptr;

            screenNeedsClear =
                true;
        }
    }
}