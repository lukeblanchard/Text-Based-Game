/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: January 10, 2018
 ** Description: Menu class implementation. Menu object takes prompts paired
 ** with variable pointers, prints prompts, asks for user input, validates user 
 ** input, and sets variables with user input
 ****************************************************************************/
#include "Menu.hpp"
#include <sstream>
#include <string> 
#include <vector> 
#include <iterator> 
#include <cctype> 


/****************************************************************************
 ** Input vector of (string, int*) pairs
 ****************************************************************************/
void Menu::getAllResponses(menuIntIO menuInt)
{
    for(menuIntIO::iterator itr = intResponses.begin(); itr != intResponses.end(); ++itr)    
    {
        std::cout << itr->first; 
        *(itr->second) = getIntegerResponse(); 
    }
}

/****************************************************************************
 ** Input vector of (string, int*) pairs, lower bound
 ****************************************************************************/
void Menu::getAllResponses(menuIntIO menuInt, int low)
{
    for(menuIntIO::iterator itr = intResponses.begin(); itr != intResponses.end(); ++itr)    
    {
        std::cout << itr->first; 
        *(itr->second) = getIntegerResponse(low); 
    }
}

/****************************************************************************
 ** Input vector of (string, int*) pairs, low-high range, and optional offset
 ****************************************************************************/
void Menu::getAllResponses(menuIntIO menuInt, int low, int high, int offset)
{
    for(menuIntIO::iterator itr = intResponses.begin(); itr != intResponses.end(); ++itr)    
    {
        std::cout << itr->first; 
        *(itr->second) = getIntegerResponse(low, high, offset); 
    }
}

/****************************************************************************
 ** Input vector of (string, double*) pairs
 ****************************************************************************/
void Menu::getAllResponses(menuDoubleIO menuDub)
{
    for(menuDoubleIO::iterator itr = doubleResponses.begin(); itr != doubleResponses.end(); ++itr)    
    {
        std::cout << itr->first; 
        *(itr->second) = getDoubleResponse(); 
    }
}

/****************************************************************************
 ** Input vector of (string, int*) pairs, lower bound
 ****************************************************************************/
void Menu::getAllResponses(menuDoubleIO menuDub, double low)
{
    for(menuDoubleIO::iterator itr = doubleResponses.begin(); itr != doubleResponses.end(); ++itr)    
    {
        std::cout << itr->first; 
        *(itr->second) = getDoubleResponse(low); 
    }
}

/****************************************************************************
 ** Input vector of (string, int*) pairs, low-high range, and optional offset
 ****************************************************************************/
void Menu::getAllResponses(menuDoubleIO menuDub, double low, double high, double offset)
{
    for(menuDoubleIO::iterator itr = doubleResponses.begin(); itr != doubleResponses.end(); ++itr)    
    {
        std::cout << itr->first; 
        *(itr->second) = getDoubleResponse(low, high, offset); 
    }
}
/****************************************************************************
 ** Input vector of (string, string*) pairs
 ****************************************************************************/
void Menu::getAllResponses(menuStringIO menuString)
{
    for(menuStringIO::iterator itr = stringResponses.begin(); itr != stringResponses.end(); ++itr)    
    {
        std::cout << itr->first; 
        getline(std::cin,*(itr->second));
        while(*(itr->second) == "")
        {
            std::cout << itr->first; 
            getline(std::cin,*(itr->second));
        }
    }
}

/****************************************************************************
 ** Input vector of (string, bool*) pairs
 ****************************************************************************/
void Menu::getAllResponses(menuBoolIO menuBool)
{
    for(menuBoolIO::iterator itr = boolResponses.begin(); itr != boolResponses.end(); ++itr)    
    {
        std::cout << itr->first; 
        *(itr->second) = getBoolResponse(); 
    }
}

/****************************************************************************
 ** Input string, check that user input is a valid int
 ****************************************************************************/
bool Menu::checkInt(std::string s)
{
    bool invalid = false; 

    for(std::string::iterator it = s.begin(); it != s.end(); ++it)
    {
        if((int) *it > 57 || (int) *it < 48) //use ASCII codes to ensure string consists of numerals 
        {
            if(it == s.begin() && (int) *it == 45) //first character may be negative sign (-)
            {
                invalid = false; 
            }
            else
            {
                invalid = true; 
            }
        }
    }
    return invalid;
}

/****************************************************************************
 ** Input string, check that user input is a valid double
 ****************************************************************************/
bool Menu::checkDouble(std::string s)
{
    bool invalid = false; 
    bool decimalPoint = false; 

    for(std::string::iterator it = s.begin(); it != s.end(); ++it)
    {
        if((int) *it > 57 || (int) *it < 48) //use ASCII codes to ensure string consists of numerals 
        {
            if(it == s.begin() && (int) *it == 45) //first character may be negative sign (-)
            {
                invalid = false; 
            }
            else if((int) *it == 46) //decimal point allowed, but only one
            {
                if(!decimalPoint)
                {
                    decimalPoint = true; 
                }
                else
                {
                    invalid = true; 
                }
            }
            else
            {
                invalid = true; 
            }
        }
    }
    return invalid;
}

/****************************************************************************
 ** Input low-high range, and offset, which can be used to correctly index
 ** row and col input
 ****************************************************************************/
int Menu::getIntegerResponse(int low, int high, int offset)
{
    int response; 
    std::string strResponse;
    bool invalid;

    std::getline(std::cin, strResponse);
    invalid = checkInt(strResponse); 

    if(!invalid)
    {
        std::istringstream istr(strResponse);
        istr >> response;   
        invalid = response < low || response > high; //input should be in this range
    }

    while(invalid) 
    {
        std::cout << "Please enter a valid choice from " << low << "-" << high << ": "; 
        std::getline(std::cin, strResponse);
        invalid = checkInt(strResponse); 
        if(!invalid)
        {
            std::istringstream istr(strResponse);
            istr >> response;   
            invalid = response < low || response > high;
        }
    }
    return response + offset;
}

/****************************************************************************
 ** Input lower bound
 ****************************************************************************/
int Menu::getIntegerResponse(int low)
{
    int response; 
    std::string strResponse;
    bool invalid;

    std::getline(std::cin, strResponse);
    invalid = checkInt(strResponse); 

    if(!invalid)
    {
        std::istringstream istr(strResponse);
        istr >> response;   
        invalid = response < low; //input should be in this range
    }

    while(invalid) 
    {
        std::cout << "Please enter a valid choice greater than or equal to " << low << ": "; 
        std::getline(std::cin, strResponse);
        invalid = checkInt(strResponse); 
        if(!invalid)
        {
            std::istringstream istr(strResponse);
            istr >> response;   
            invalid = response < low;
        }
    }
    return response; 
}
/****************************************************************************
 ** Get integer, no range check or offset
 ****************************************************************************/
int Menu::getIntegerResponse()
{
    int response; 
    std::string strResponse;
    bool invalid;
    bool stringEmpty = false; 

    std::getline(std::cin, strResponse);
    if(strResponse == "")
    {
        stringEmpty = true;
    }
    invalid = checkInt(strResponse); 

    while(invalid || stringEmpty) 
    {
        std::cout << "Please enter a valid number: ";  
        std::getline(std::cin, strResponse);
        if(strResponse == "")
        {
            stringEmpty = true;
        }
        else
        {
            stringEmpty = false;
        }
        invalid = checkInt(strResponse); 
    }

    std::istringstream istr(strResponse);
    istr >> response;
    return response;
}

/****************************************************************************
 ** Input low-high range, and offset, which can be used to correctly index
 ** row and col input
 ****************************************************************************/
double Menu::getDoubleResponse(double low, double high, double offset)
{
    double response; 
    std::string strResponse;
    bool invalid;

    std::getline(std::cin, strResponse);
    invalid = checkDouble(strResponse); 

    if(!invalid)
    {
        std::istringstream istr(strResponse);
        istr >> response;   
        invalid = response < low || response > high; //input should be in this range
    }

    while(invalid) 
    {
        std::cout << "Please enter a valid choice from " << low << "-" << high << ": "; 
        std::getline(std::cin, strResponse);
        invalid = checkDouble(strResponse); 
        if(!invalid)
        {
            std::istringstream istr(strResponse);
            istr >> response;   
            invalid = response < low || response > high;
        }
    }
    return response + offset;
}

/****************************************************************************
 ** Input lower bound
 ****************************************************************************/
double Menu::getDoubleResponse(double low)
{
    double response; 
    std::string strResponse;
    bool invalid;

    std::getline(std::cin, strResponse);
    invalid = checkInt(strResponse); 

    if(!invalid)
    {
        std::istringstream istr(strResponse);
        istr >> response;   
        invalid = response < low; //input should be in this range
    }

    while(invalid) 
    {
        std::cout << "Please enter a valid choice greater than or equal to " << low << ": "; 
        std::getline(std::cin, strResponse);
        invalid = checkDouble(strResponse); 
        if(!invalid)
        {
            std::istringstream istr(strResponse);
            istr >> response;   
            invalid = response < low;
        }
    }
    return response; 
}
/****************************************************************************
 ** Get integer, no range check or offset
 ****************************************************************************/
double Menu::getDoubleResponse()
{
    double response; 
    std::string strResponse;
    bool invalid;

    std::getline(std::cin, strResponse);
    invalid = checkDouble(strResponse); 

    while(invalid) 
    {
        std::cout << "Please enter a valid number: ";  
        std::getline(std::cin, strResponse);
        invalid = checkDouble(strResponse); 
    }

    std::istringstream istr(strResponse);
    istr >> response;
    return response;
}

/****************************************************************************
 ** Get yes/no string input
 ****************************************************************************/
bool Menu::getBoolResponse()
{
    std::string strResponse;
    bool invalid;

    std::getline(std::cin, strResponse);
    invalid = checkBool(&strResponse); 

    while(invalid) 
    {
        std::cout << "Please enter 'y' or 'n': ";  
        std::getline(std::cin, strResponse);
        invalid = checkBool(&strResponse); 
    }
    if(strResponse == "NO" || strResponse == "N")
        return false; 
    else
        return true;
}


/****************************************************************************
 ** Check yes/no string input
 ****************************************************************************/
bool Menu::checkBool(std::string *resp) 
{
    for(std::string::iterator it = resp->begin(); it != resp->end(); ++it)
    {
        *it = toupper(*it); 
    }

    if(*resp != "NO" && *resp != "N" && *resp != "YES" && *resp != "Y")
        return true; 
    else
        return false;
}

/****************************************************************************
 ** Input vector of (string, int*) pairs
 ****************************************************************************/
void Menu::load(menuIntIO newPAndR)
{
    intResponses = newPAndR;
    getAllResponses(intResponses);  
}

/****************************************************************************
 ** Input vector of (string, int*) pairs, lower bound
 ****************************************************************************/
void Menu::load(menuIntIO newPAndR, int low)
{
    intResponses = newPAndR;
    getAllResponses(intResponses, low);  
}

/****************************************************************************
 ** Input vector of (string, int*) pairs, low-high range, optional offset
 ****************************************************************************/
void Menu::load(menuIntIO newPAndR, int low, int high, int offset)
{
    intResponses = newPAndR;
    getAllResponses(intResponses, low, high, offset);  
}

/****************************************************************************
 ** Input vector of (string, double*) pairs
 ****************************************************************************/
void Menu::load(menuDoubleIO newPAndR)
{
    doubleResponses = newPAndR;
    getAllResponses(doubleResponses);  
}

/****************************************************************************
 ** Input vector of (string, double*) pairs, lower bound
 ****************************************************************************/
void Menu::load(menuDoubleIO newPAndR, double low)
{
    doubleResponses = newPAndR;
    getAllResponses(doubleResponses, low);  
}

/****************************************************************************
 ** Input vector of (string, double*) pairs, low-high range, optional offset
 ****************************************************************************/
void Menu::load(menuDoubleIO newPAndR, double low, double high, double offset)
{
    doubleResponses = newPAndR;
    getAllResponses(doubleResponses, low, high, offset);  
}
/****************************************************************************
 ** Input vector of (string, string*) pairs
 ****************************************************************************/
void Menu::load(menuStringIO newPAndR)
{
    stringResponses = newPAndR;
    getAllResponses(stringResponses);
}

/****************************************************************************
 ** Input vector of (string, bool*) pairs
 ****************************************************************************/
void Menu::load(menuBoolIO newPAndR)
{
    boolResponses = newPAndR;
    getAllResponses(boolResponses); 
}

