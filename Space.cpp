/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 6, 2018
 ** Description: Implementation file for Space class 
 ****************************************************************************/
#include "Space.hpp"

Space::Space(int c)
{
    contents = c; 
    for(int i = 0; i < 4; i++)
    {
        surroundingSpaces.push_back(nullptr); //initialize surrounding spaces to nullptr
    }
}

/****************************************************************************
 ** Used during setup
 ****************************************************************************/
void Space::setAdjacentSpace(Space* sp, int direction)
{
    surroundingSpaces[direction] = sp; 
}

/****************************************************************************
 ** Used when player moves, needs to change current space
 ****************************************************************************/
Space* Space::getDirection(int direction) 
{
    return surroundingSpaces[direction]; 
}

int Space::getContents()
{
    return contents;
}

void Space::clearAdjacentSpaces()
{
    for(int i = 0; i < 4; i++)
    {
        surroundingSpaces[i] = nullptr;
    }
}

void Space::printSurroundings()
{
    std::string allDirections = ""; 
    std::string north = ""; 
    std::string south = ""; 
    std::string west = ""; 
    std::string east = ""; 

    for(int i = 0; i < 4; i++)
    {
        switch(i)
        {
            case(0): 
                north += "1.North: "; 
                if(surroundingSpaces[i] == nullptr) 
                {
                    north += "Wall\n"; 
                }
                else
                {
                    north += surroundingSpaces[i]->printContents(); 
                }
                break;
            case(1): 
                east = "4.East: "; 
                if(surroundingSpaces[i] == nullptr) 
                {
                    east += "Wall\n"; 
                }
                else
                {
                    east += surroundingSpaces[i]->printContents(); 
                }
                break;
            case(2): 
                south = "2.South: "; 
                if(surroundingSpaces[i] == nullptr) 
                {
                    south += "Wall\n";
                }
                else
                {
                    south += surroundingSpaces[i]->printContents(); 
                }
                break;
            case(3): 
                west = "3.West: "; 
                if(surroundingSpaces[i] == nullptr) 
                {
                    west += "Wall\n";
                }
                else
                {
                    west += surroundingSpaces[i]->printContents(); 
                }
                break;
        }
    }
    allDirections = north + south + west + east; 
    std::cout << std::endl; 
    std::cout << allDirections << std::endl;
}

Space::~Space(){}
