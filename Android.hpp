/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Header file for Android class 
 ****************************************************************************/

#ifndef ANDROID_HPP
#define ANDROID_HPP
#include "Space.hpp"
#include <string> 
#include <iostream> 

class Android : public Space
{
private:
    std::string words;  
    int charge; //track life in combat
    bool alive; //shows different message, if alive or dead
public: 
    Android(int, int, std::string); 
    void speak();
/****************************************************************************
 ** Function to decrease charge points during combat
 ****************************************************************************/
    void decreaseCharge(int); 
    int getCharge(); 
/****************************************************************************
 ** Good androids help, bad androids attack
 ****************************************************************************/
    virtual int interact() = 0; 
    virtual std::string printContents(); 
    bool getLifeStatus(); 
}; 

#endif
