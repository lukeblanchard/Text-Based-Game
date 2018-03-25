/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: January 21, 2018
 ** Description: Header file for Dice class
 ****************************************************************************/
#ifndef DIE_HPP
#define DIE_HPP
#include <iostream>

class Die 
{
private: 
    int N; 
public:
    Die(int); 
    int getSides(); 
    int roll(); 
};

#endif
