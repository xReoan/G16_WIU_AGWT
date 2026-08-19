#include "Game.h"

#include "iostream"
#include <cstdlib>
#include <ctime>

int main()
{
    // Gives rand() a different seed
    // whenever the program starts.
    srand(time(0));
    //start screen
        std::cout << R"(
 _______    _______  _______  __   __  _______    _     _  ___   _______  __   __ 
|   _   |  |       ||   _   ||  |_|  ||       |  | | _ | ||   | |       ||  | |  |
|  |_|  |  |    ___||  |_|  ||       ||    ___|  | || || ||   | |_     _||  |_|  |
|       |  |   | __ |       ||       ||   |___   |       ||   |   |   |  |       |
|       |  |   ||  ||       ||       ||    ___|  |       ||   |   |   |  |       |
|   _   |  |   |_| ||   _   || ||_|| ||   |___   |   _   ||   |   |   |  |   _   |
|__| |__|  |_______||__| |__||_|   |_||_______|  |__| |__||___|   |___|  |__| |__|

                                        
              mmmmmmmm  mm    mm  mmmmmmmm  mmm  mmm 
              """##"""  ##    ##  ##""""""  ###  ### 
                 ##     ##    ##  ##        ######## 
                 ##     ########  #######   ## ## ## 
                 ##     ##    ##  ##        ## "" ## 
                 ##     ##    ##  ##mmmmmm  ##    ##  ##
                 ""     ""    ""  """"""""  ""    ""  ""
	)" << std::endl;;
    system("pause");
	system("cls");
	
    //then the fuctions below
    
    Map* gameMap = new Map();

    Game game;

    game.run();

    return 0;
}
