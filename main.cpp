#include "RunMap.h"
#include <iostream>

int main()
{
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

    //then the fuctions below
	return 0;
    
    Map* gameMap = new Map();

    gameMap->createTestMap();
    gameMap->drawMap();

    delete gameMap;
    gameMap = nullptr;

    return 0;
}
