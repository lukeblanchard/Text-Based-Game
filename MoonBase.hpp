/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Header file for MoonBase class 
 ****************************************************************************/

#ifndef MOONBASE_HPP
#define MOONBASE_HPP
#include "Space.hpp"
#include "EscapePod.hpp"
#include "GoodDroid.hpp"
#include "BadDroid.hpp"
#include "OpenSpace.hpp"
#include <iostream>
#include <iomanip>

class MoonBase
{
//Blueprint used for creating spaces, and printing map: -1 is null (wall), -2 is wall (also null, but needs to be printed in the map)
//2 is escape pod, and 0 is open space
const int BLUEPRINT[11][13] = 
{{-1,-1,-1,-1,-1,-2,-2,-2,-1,-1,-1,-1,-1,},
{-1,-1,-1,-1,-1,-2,2,-2,-1,-1,-1,-1,-1,},
{-1,-1,-2,-2,-2,-2,0,-2,-2,-2,-2,-1,-1,},
{-1,-1,-2,0,0,0,0,0,0,0,-2,-1,-1,},
{-1,-1,-2,0,0,-2,0,-2,0,0,-2,-1,-1,},
{-2,-2,-2,-2,-2,-2,0,-2,-2,-2,-2,-2,-2,},
{-2,2,0,0,0,0,0,0,0,0,0,2,-2},
{-2,-2,-2,-2,-2,-2,0,-2,-2,-2,-2,-2,-2,},
{-1,-1,-2,0,0,-2,0,-2,0,0,-2,-1,-1,},
{-1,-1,-2,0,0,0,0,0,0,0,-2,-1,-1,},
{-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,}};

private: 
    Space*** baseMap; //pointer to a 2D array of Space* 
    int mapWidth; 
    int mapLength;
    int* accessCode; //passed to escape pod and good droid
    int workingPod; //number to track which pod works and has full fuel tank
    int noFuelPod; //number to track which pod works, but needs fuel
    int goodDroidRow; //one random row has the good droid
public:
    MoonBase(); 
/****************************************************************************
 ** Loops through baseMap, creating OpenSpace or EscapePod objects, or leaves
        Space as nullptr, which indicates wall
 ****************************************************************************/
    void initializeMap(Space***);
/****************************************************************************
 ** links the spaces, north, south, east, west
 ****************************************************************************/
    void createLinks();
/****************************************************************************
 ** Create random access code
 ****************************************************************************/
    void initializeCode(int*); 
    void printMap(Space*); 
/****************************************************************************
 ** Returns center, which is starting location for player
 ****************************************************************************/
    Space* getCenter(); 

/****************************************************************************
 ** Sets random row for good droid location
 ****************************************************************************/
    int setGoodDroidRow(); 

/****************************************************************************
 ** Places droids in random spaces throughout base
 ****************************************************************************/
    void addDroids(); 
    ~MoonBase();
}; 

#endif
