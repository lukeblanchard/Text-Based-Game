/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Implementation for BadDroid class  
 ****************************************************************************/
#include "BadDroid.hpp"

BadDroid::BadDroid(int energy) : Android(energy, 2, "Death to humans!")
{
    blaster = new Die(4); 
    shield = new Die(5); 
    alive = true; 
}

int BadDroid::interact()
{
    int attack = blaster->roll();
    return attack;
}

void BadDroid::defend(int attackForce)
{
    int defense = shield->roll(); 
    if(attackForce > defense)
    {
        std::cout << "\tThe android loses " << attackForce << " energy points!" << std::endl; 
        decreaseCharge(attackForce);   
    }
    else if(attackForce == 0) //happens when player has no blaster in supplies
    {
        std::cout << "'Humans are weak and foolish!' cries the android." << std::endl;
    }
    else
    {
        std::cout << "\tThe android deflects your shot!" << std::endl;  
    }
}

BadDroid::~BadDroid()
{
    delete blaster;
    delete shield;
}
