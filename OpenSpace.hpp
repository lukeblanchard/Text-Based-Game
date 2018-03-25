/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Header file for OpenSpace class 
 ****************************************************************************/

#ifndef OPENSPACE_HPP
#define OPENSPACE_HPP
#include "Space.hpp"

class OpenSpace : public Space
{
private: 
    int object; 
public: 
    OpenSpace(); 
/****************************************************************************
 ** Objects are represented by integers, when a player takes an object from 
    a space, the space is set to empty, and thereafter returns 0
 ****************************************************************************/
    void setToEmpty(); 
/****************************************************************************
 ** If a player leaves, an object, the space will then hold that left object
 ****************************************************************************/
    void setObject(int); 

/****************************************************************************
 ** If not empty, interact() prints a message and returns an integer
        corresponding to an object: fuel, medicine, blaster, forcefield
 ****************************************************************************/
    virtual int interact(); 
    virtual std::string printContents(); 
}; 

#endif
