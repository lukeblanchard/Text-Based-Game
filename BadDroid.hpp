/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Header file for BadDroid class 
 ****************************************************************************/

#ifndef BADDROID_HPP
#define BADDROID_HPP
#include "Die.hpp"
#include "Android.hpp"

class BadDroid : public Android
{
private: 
    Die* blaster;
    Die* shield; 
    bool alive;
public:
    BadDroid(int); 
    int attack(); 
/****************************************************************************
 ** Interaction for bad android is combat
 ****************************************************************************/
    int interact(); 
    void defend(int); 
    ~BadDroid(); 
}; 

#endif
