#include "Game.h"

#include <cstdlib>
#include <ctime>

int main()
{
    // Gives rand() a different seed
    // whenever the program starts.
    srand(time(0));

    Game game;

    game.run();

    return 0;
}