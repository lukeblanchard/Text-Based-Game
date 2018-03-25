/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Header file for Player class
 ****************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Space.hpp"
#include "BadDroid.hpp"
#include "GoodDroid.hpp"
#include "OpenSpace.hpp"
#include "EscapePod.hpp"
#include "Menu.hpp"
#include "Die.hpp"
#include <string> 
#include <vector> 
#include <algorithm> 

class Player 
{
enum ITEMS {Medicine, ForceField, Blaster, Fuel, Drive}; 
const int ITEMLIMIT = 4;
const int STEPLIMIT = 30; 

private:
    Space* currentSpace;
    int steps; 
    int health; 
    int numberItems;
    int blasterCount;
    int medicineCount;
    int forceFieldCount;
    int fuelCanisterCount; 
    Die* blaster;
    Die* forceField;
    std::vector<int> supplies;
    Menu* menu;
    bool gameOver; 
    bool lose; 
public: 
/****************************************************************************
 ** Constructor takes Space pointer, starting location
 ****************************************************************************/
    Player(Space*);    
/****************************************************************************
 ** Changes current space
 ****************************************************************************/
    void move(Space*); 
/****************************************************************************
 ** Prints messages and calls Space::interact() for each moved-to space 
 ****************************************************************************/
    void engageSpace(int); //each space type has an associated integer, and each space returns an int from interact()
/****************************************************************************
 ** Functions to fight bad droids
 ****************************************************************************/
    void combat(); 
    void defend(int); 
    int attack(); 
    int getHealth(); 
    int getSteps(); 
/****************************************************************************
 ** Allows player to add found object to supplies
 ****************************************************************************/
    void chooseSupplies(); 
    void printSupplies(); 
    void printStats(); //prints health, remaining steps, and supplies 
/****************************************************************************
 ** If player needs to leave an item, createItemsMenu() creates a menu, 
        so player can choose item to leave from supplies
 ****************************************************************************/
    std::string createItemsMenu();
    Space* getCurrentLocation(); 
    void getPassCode(); //interact good droid
    void engagePod(); //interact escape pod
    bool getGameOver(); //see if game is over
    bool getLose(); //see if player lost
    ~Player();
}; 

#endif
