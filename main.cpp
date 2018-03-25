/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: main  
 ****************************************************************************/
#include "MoonBase.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <stdlib.h>
#include <time.h>

int main() 
{
    srand(time(NULL));  
    Game game;
    game.play(); 
    return 0;
}
