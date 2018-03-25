/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Implementation for Android class  
 ****************************************************************************/
#include "Android.hpp"

Android::Android(int energy, int type, std::string w) : Space(type)
{
    words = w; 
    charge = energy;
    alive = true;
}

void Android::speak()
{
    std::cout << words << std::endl;
}

void Android::decreaseCharge(int hit)
{
    charge -= hit; 
    if(charge <= 0)
    {
        alive = false;
    }
}

int Android::getCharge()
{
    return charge;
}

std::string Android::printContents() //used when printing directions for player, both good and bad androids have the same label
{
    return "Android\n";
}

bool Android::getLifeStatus()
{
    return alive;
}
