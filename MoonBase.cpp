/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Implementation file for MoonBase class 
 ****************************************************************************/
#include "MoonBase.hpp"

MoonBase::MoonBase()
{
    mapWidth = 11; 
    mapLength = 13; 
    workingPod = rand() % 3 + 1; 
    noFuelPod = rand() % 3 + 1; 
    while(noFuelPod == workingPod)
    {
        noFuelPod = rand() % 3 + 1; 
    }
    accessCode = new int[4]; 
    goodDroidRow = setGoodDroidRow(); 
    initializeCode(accessCode); 
    baseMap = new Space**[mapWidth]; 
    initializeMap(baseMap); 
}

int MoonBase::setGoodDroidRow()
{
    int goodRow = rand() % 7 + 3;
    while(goodRow == 5 || goodRow == 7)
    {
        goodRow = rand() % 7 + 3;
    }
    return goodRow;  
}

void MoonBase::initializeMap(Space*** map)
{
    for(int i = 0; i < mapWidth; i++)
    {
        map[i] = new Space*[mapLength];
        for(int j = 0; j < mapLength; j++)
        {
            switch(BLUEPRINT[i][j])
            {
                case(-1):
                case(-2): 
                    map[i][j] = nullptr; 
                    break; 
                case(0):
                    map[i][j] = new OpenSpace(); 
                    break;
                case(2):
                    if(i == 1)
                    {
                        if(workingPod == 2)
                        {
                            map[i][j] = new EscapePod(true, accessCode); 
                        }
                        else if(noFuelPod == 2)
                        {
                            map[i][j] = new EscapePod(false, accessCode); 
                        }
                        else
                        {
                            map[i][j] = new EscapePod(false);  
                        }
                    }
                    if(i == 6)
                    {
                        if(j == 1)
                        {
                            if(workingPod == 1)
                            {
                                map[i][j] = new EscapePod(true, accessCode); 
                            }
                            else if(noFuelPod == 1)
                            {
                                map[i][j] = new EscapePod(false, accessCode); 
                            }
                            else
                            {
                                map[i][j] = new EscapePod(false);  
                            }
                        }
                        if(j == 11)
                        {
                            if(workingPod == 3)
                            {
                                map[i][j] = new EscapePod(true, accessCode); 
                            }
                            else if(noFuelPod == 3)
                            {
                                map[i][j] = new EscapePod(false, accessCode); 
                            }
                            else
                            {
                                map[i][j] = new EscapePod(false);  
                            }
                        }
                    }
                    break;
            }
        }
    }
    addDroids(); 
    createLinks(); 
}

void MoonBase::addDroids()
{
    int droidCol;
    for(int row = 3; row < 10; row++)
    {
        droidCol = rand() % 6 + 3;     
        while(BLUEPRINT[row][droidCol] != 0) //while not an open space
        {
            droidCol = rand() % 6 + 3;     
        }
        while(row == 6 && droidCol == 6) //if center space
        {
            droidCol = rand() % 6 + 3;     
        }
        for(int col = 3; col < 11; col++)
        {
            if(col == droidCol && row != 5 && row != 7)
            {
                delete baseMap[row][droidCol]; 
                if(row == goodDroidRow)
                {
                    baseMap[row][col] = new GoodDroid(accessCode);
                }
                else
                {
                    baseMap[row][col] = new BadDroid(rand() % 8 + 1);
                }
            }
        }
    }
}

void MoonBase::createLinks()
{
    for(int row = 0; row < mapWidth; row++)
    {
        for(int col = 0; col < mapLength; col++)
        {
            if(baseMap[row][col] != nullptr)
            {
                baseMap[row][col]->setAdjacentSpace(baseMap[row-1][col], 0);  
                baseMap[row][col]->setAdjacentSpace(baseMap[row][col+1], 1);  
                baseMap[row][col]->setAdjacentSpace(baseMap[row+1][col], 2);  
                baseMap[row][col]->setAdjacentSpace(baseMap[row][col-1], 3);  
            }
        }
    }
}

void MoonBase::initializeCode(int* code)
{
    for(int i = 0; i < 4; i++)
    {
        code[i] = rand() % 4;  
    }
}

void MoonBase::printMap(Space* playerLocation)
{
    std::cout << std::endl; 
    std::cout << "Base Map" << std::endl; 
    std::cout << "------------" << std::endl;
    for(int row = 0; row < mapWidth; row++)
    {
        for(int col = 0; col < mapLength; col++)
        {
            if(baseMap[row][col] == nullptr)
            {
                if(BLUEPRINT[row][col] == -2)
                {
                    std::cout << "+"; 
                }
                else
                {
                    std::cout << " "; 
                }
            }
            else if(baseMap[row][col] == playerLocation)
            {
                std::cout << "P";  
            }
            else if(baseMap[row][col]->getContents() == 1 || baseMap[row][col]->getContents() == 2) 
            {
                std::cout << "*";
            }
            else if(baseMap[row][col]->getContents() == 3)
            {
                std::cout << "E"; 
            }
            else
            {
                std::cout << " ";  
            }
        }
        std::cout << std::endl; 
    }
    std::cout << std::endl; 
}

Space* MoonBase::getCenter()
{
    OpenSpace* center = static_cast<OpenSpace*>(baseMap[6][6]);  
    center->setToEmpty(); 
    return baseMap[6][6]; 
}
//free memory
MoonBase::~MoonBase()
{
    for(int r = 0; r < mapWidth; r++)
    {
        for(int c = 0; c < mapLength; c++)
        {
            if(baseMap[r][c] != nullptr)
            {
                baseMap[r][c]->clearAdjacentSpaces(); 
                delete baseMap[r][c];
            }
        }
        delete [] baseMap[r]; 
    }
    delete [] baseMap; 
    delete [] accessCode; 
}
