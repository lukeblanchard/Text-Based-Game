/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 6, 2018
 ** Description: Header for abstract class Space 
 ****************************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP
#include <vector> 
#include <iostream>
#include <string>

class Space
{
    enum SPACES {Open, GoodDroid, BadDroid, EscapePod}; 

private: 
    std::vector<Space*> surroundingSpaces; //top/North: 0, right/East: 1, down/South: 2, left/West: 3
    int contents; 
public: 
/****************************************************************************
 ** Constructor takes an integer corresponding to type of Space
 ****************************************************************************/
    Space(int); 
    virtual std::string printContents() = 0; 
    int getContents(); 
/****************************************************************************
 ** Create links between the spaces, store pointer in surroundingSpaces
 ****************************************************************************/
    void setAdjacentSpace(Space*, int);
/****************************************************************************
 ** Set surroundingSpaces to nullptr, prevents dangling pointers
 ****************************************************************************/
    void clearAdjacentSpaces(); 
/****************************************************************************
 ** Prints surrounding spaces, so player can choose direction
 ****************************************************************************/
    void printSurroundings(); 
/****************************************************************************
 ** Each type of space interacts differently with player
 ****************************************************************************/
    virtual int interact() = 0;
    Space* getDirection(int); //return space pointer from surroundingSpaces vector
    virtual ~Space();
}; 

#endif
