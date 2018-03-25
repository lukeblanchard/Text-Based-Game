/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 8, 2018
 ** Description: Header file for Game class 
 ****************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP
#include "MoonBase.hpp"
#include "Space.hpp"
#include "Player.hpp"
#include "Menu.hpp"

class Game
{

const int STEPLIMIT = 30; 

private: 
    MoonBase* base; 
    Player* player; 
    Menu* menu;
    bool begin; 
public: 
    Game(); 
/****************************************************************************
 ** The play function loops while character has strength, steps, and has not won
 ****************************************************************************/
    void play(); 
/****************************************************************************
 ** Prints intro information
 ****************************************************************************/
    void intro(); 
    ~Game();
}; 

#endif
