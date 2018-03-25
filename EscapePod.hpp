/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Header file for EscapePod class 
 ****************************************************************************/

#ifndef ESCAPEPOD_HPP
#define ESCAPEPOD_HPP
#include "Space.hpp"

class EscapePod : public Space
{
private: 
    int* accessCode; 
    bool escape; 
    bool fuelTank;
public: 
/****************************************************************************
 ** Bool indicates if escape pod has fuel or not; two escape pods get the 
        access code, and one of those has no fuel
 ****************************************************************************/
    EscapePod(bool, int* code=nullptr);  
/****************************************************************************
 ** If escape pod has code, the interact function asks for access code
 ****************************************************************************/
    virtual int interact(); 
    int interactWrapper(bool);
    virtual std::string printContents(); 
}; 

#endif
