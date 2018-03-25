/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Implementation of OpenSpace class 
 ****************************************************************************/
#include "OpenSpace.hpp"

OpenSpace::OpenSpace() : Space(0)
{
    object = rand() % 16 + 1;  //with 16 possible numbers, and 4 objects, roughly 25% of spaces will have objects
}

int OpenSpace::interact()
{
    std::cout << std::endl; 
    switch(object) 
    {
        case(0):
        case(1):
        case(2):
        case(3):
        case(4):
        case(5): 
            return 0; //more empty spaces than objects
            break;
        case(6):
            std::cout << "You found medicine. If your strength falls below 20%\n" 
                      << "medicine gives you two extra strength points" << std::endl; 
            std::cout << std::endl; 
            return 1; //medicine
            break;
        case(7):
            std::cout << "You found another blaster. If you have multiple blasters\n" 
                      << "in your supplies, your attacking power multiplies." << std::endl;
            std::cout << std::endl; 
            return 2; //better blaster
        case(8):
            std::cout << "You found a fuel pack. If you choose an escape pod\n"
                      << "with no fuel, you can use this fuel pack to refuel and escape." << std::endl;
            std::cout << "But you still need the access code." << std::endl;
            std::cout << std::endl; 
            return 3; //fuel canister
            break;
        case(9):
            std::cout << "You found a force field that defends against attacks.\n"
                      << "If you have multiple force fields, your defending power multiplies." << std::endl;
            std::cout << std::endl; 
            return 4;
            break;
        default: //also catches empty spaces
            return 0;
            break;
    }
}

void OpenSpace::setToEmpty()
{
    object = 0;
}

void OpenSpace::setObject(int obj)
{
    object = obj;
}

std::string OpenSpace::printContents()
{
    return "Open Space\n";
}
