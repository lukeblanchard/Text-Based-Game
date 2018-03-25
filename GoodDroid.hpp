/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Header for good android 
 ****************************************************************************/

#ifndef GOODDROID_HPP
#define GOODDROID_HPP
#include "Android.hpp"
#include <string> 

class GoodDroid : public Android
{
private: 
    int* accessCode; //random four digit code generated every game 
    bool alive;
public: 
    GoodDroid(int*); 
/****************************************************************************
 ** Good Droid gives player access code(random four digit sequence), 
        and the hard drive (represented by the integer 5)
 ****************************************************************************/
    int interact(); 
    bool getAlive(); 
    void setAlive(bool); 
};

#endif
