/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: January 21, 2018
 ** Description: Implementation for Die class 
 ****************************************************************************/
#include "Die.hpp"

Die::Die(int sides)
    :N(sides)
    {
    }

int Die::getSides()
{
    return N;
}

/****************************************************************************
 ** Uses rand() to output a number between 1 and N
 ****************************************************************************/
int Die::roll()
{
    int roll;
    roll = rand() % N + 1; 
    return roll; 
}
