#include "Game.h"

#include <cstdlib>
#include <ctime>

int main()
{
    // Gives rand() a different seed
    // based on the current time.
    srand(time(0));

    Game game;

    game.run();

    return 0;
}