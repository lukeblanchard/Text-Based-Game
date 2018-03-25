/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Implementation for GoodDroid class 
 ****************************************************************************/
#include "GoodDroid.hpp"

GoodDroid::GoodDroid(int* code) : Android(3, 1, "Your wish is my command.")
{
    accessCode = code;  //code generated in Game class, passed to both good droid and escape pods
    alive = true; 
}

int GoodDroid::interact()
{
    if(alive)
    {
        std::cout << "You found the single android not infected with the virus!" << std::endl; 
        std::cout << std::endl; 
        std::cout << "Rmember the following access code: " << std::endl; 
        for(int i = 0; i < 4; i++)
        {
            std::cout << accessCode[i] << " "; 
        }
        std::cout << std::endl; 
        std::cout << std::endl; 
        std::cout << "You must also carry a hard drive that contains information about the virus that breached the system." << std::endl;
        std::cout << "If you escape without this drive, the CORPORATION will sentence you to a life of hard labor on a sand worm planet!" << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "This android is dead." << std::endl;
    }
    return 0;
}

bool GoodDroid::getAlive()
{
    return alive;
}

void GoodDroid::setAlive(bool b)
{
    alive = b;
}
