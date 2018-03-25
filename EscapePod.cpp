/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Implementation for EscapePod class 
 ****************************************************************************/
#include "EscapePod.hpp"

EscapePod::EscapePod(bool fuel, int* code) : Space(3)
{
    accessCode = code; 
    escape = false; 
    fuelTank = fuel;
}

std::string EscapePod::printContents()
{
    return "Escape Pod\n";
}
//The Space::interact function has no parameters, but we need to know if player has fuel
//The interactWrapper function has a boolean parameter. When player interacts with pod, the class
//passes a boolean indicating if there is fuel canister in the supplies
int EscapePod::interactWrapper(bool fuel) 
{
    int pod = interact(); 
    if(pod == 1)
    {
        if(!fuelTank && fuel == 0)
        {
            std::cout << "Oh no! The fuel tank is empty,\n"
                      << "and you don't have a fuel canister in your supplies!\n" 
                      << "You need to find another pod, or find a fuel canister!" << std::endl;  
            return 0;
        }
        if(!fuelTank && fuel > 0)
        {
           std::cout << "The fuel tank is empty, but you have a fuel canister in your supplies!" << std::endl; 
           return 1;
        }
    }
    return pod; //1 and the player escapes, 0 and there was a problem
}

int EscapePod::interact()
{   
    if(accessCode == nullptr)
    {
        std::cout << "The androids disabled this escape pod! You must find another!" << std::endl; 
        return 0; 
    }
    else
    {
        std::string playerCode; 
        std::string actualCode;
        std::cout << "You found the correct escape pod!" << std::endl; 
        std::cout << "Please input the access code, without spaces, and press enter: " << std::endl;
        std::getline(std::cin, playerCode); 
        for(int i = 0; i < 4; i++)
        {
            actualCode += std::to_string(accessCode[i]); 
        }
        if(playerCode == actualCode)
        {
            std::cout << "Escape pod engaged!" << std::endl;
            return 1; 
        }
        else
        {
            std::cout << "You entered the incorrect pass code!" << std::endl;
            return 0;
        }
    }
}
