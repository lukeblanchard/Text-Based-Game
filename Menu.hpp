/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: January 10, 2018
 ** Description: Menu class header file
 ****************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <iostream> 
#include <string>
#include <vector>

//type definitions to handle different menu scenarios: int input, string input, yes/no input
typedef std::pair<std::string, int*> menuIntPrompts; 
typedef std::pair<std::string, double*> menuDoublePrompts; 
typedef std::pair<std::string, std::string*> menuStringPrompts; 
typedef std::pair<std::string, bool*> menuBoolPrompts; 
typedef std::vector<menuIntPrompts> menuIntIO; 
typedef std::vector<menuDoublePrompts> menuDoubleIO; 
typedef std::vector<menuStringPrompts> menuStringIO; 
typedef std::vector<menuBoolPrompts> menuBoolIO; 

class Menu 
{
private: 
    menuIntIO intResponses;
    menuDoubleIO doubleResponses;
    menuStringIO stringResponses;
    menuBoolIO boolResponses;
public:
    void load(menuIntIO); 
    void load(menuIntIO, int, int, int offset = 0); 
    void load(menuIntIO, int); 
    void load(menuDoubleIO); 
    void load(menuDoubleIO, double, double, double offset = 0); 
    void load(menuDoubleIO, double); 
    void load(menuStringIO); 
    void load(menuBoolIO); 

    void getAllResponses(menuIntIO); 
    void getAllResponses(menuIntIO, int); 
    void getAllResponses(menuIntIO, int, int, int); 
    void getAllResponses(menuDoubleIO); 
    void getAllResponses(menuDoubleIO, double); 
    void getAllResponses(menuDoubleIO, double, double, double); 
    void getAllResponses(menuStringIO); 
    void getAllResponses(menuBoolIO); 

    
    int getIntegerResponse(int, int, int); 
    int getIntegerResponse(int); 
    int getIntegerResponse(); 
    bool checkInt(std::string);

    double getDoubleResponse(double, double, double); 
    double getDoubleResponse(double); 
    double getDoubleResponse(); 
    bool checkDouble(std::string);


    bool getBoolResponse(); 
    bool checkBool(std::string*); 
};

#endif
