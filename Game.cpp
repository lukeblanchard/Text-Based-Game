/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 8, 2018
 ** Description: Implementation file for Game class 
 ****************************************************************************/
#include "Game.hpp"

Game::Game()
{
    base = new MoonBase();  
    menu = new Menu;
    Space* center = base->getCenter(); 
    player = new Player(center); 
    intro(); 
}

void Game::play()
{
    int direction; 
    Space* location; //current location of player
    Space* newLocation; //new location of player after move 

    menuIntIO getNewLocation;
    getNewLocation.push_back(std::make_pair("Which way do you want to go?\nEnter your choice as a number: ", &direction)); 

    menuIntIO error; 
    error.push_back(std::make_pair("You cannot move through walls. Please enter another choice: ", &direction)); 

    if(begin)
    {
        location = player->getCurrentLocation(); 
        base->printMap(location); 
        player->printStats(); 

        while(player->getHealth() > 0 && player->getSteps() < STEPLIMIT && !player->getGameOver())
        {
            location->printSurroundings(); 
            menu->load(getNewLocation, 1, 4); 

            switch(direction)
            {
                case(1): //north
                    newLocation = location->getDirection(0); //in the space class, north = 0, east = 1, south = 2, west = 3, in a clockwise
                    break; 
                case(2): //south
                    newLocation = location->getDirection(2); 
                    break;
                case(3): //west 
                    newLocation = location->getDirection(3); 
                    break;
                case(4): //east
                    newLocation = location->getDirection(1); 
                    break;
            }

            while(newLocation == nullptr)
            {
                menu->load(error, 1, 4); 
                switch(direction)
                {
                    case(1):
                        newLocation = location->getDirection(0); 
                        break; 
                    case(2):
                        newLocation = location->getDirection(2); 
                        break;
                    case(3):
                        newLocation = location->getDirection(3); 
                        break;
                    case(4):
                        newLocation = location->getDirection(1); 
                        break;
                }
            }

            location = newLocation;
            base->printMap(location); 
            player->move(location);
            player->printStats(); 
        }
        //check why the game ended, and print corresponding message
        if(player->getHealth() <= 0)
        {
            std::cout << "You have lost all health points!" << std::endl; 
            std::cout << "GAME OVER!" << std::endl; 
        }
        if(player->getSteps() >= STEPLIMIT)
        {
            std::cout << "The moon base has run out of oxygen!" << std::endl;
            std::cout << "GAME OVER!" << std::endl; 
        }
        if(player->getGameOver())
        {
            std::cout << "You escaped and won the game!" << std::endl;
            std::cout << "CONGRATULATIONS!" << std::endl;
        }
    }
    else
    {
        std::cout << "Goodbye!" << std::endl;
    }
}

void Game::intro()
{
    menuBoolIO beginPlay;
    beginPlay.push_back(std::make_pair("Are you ready to begin? (y/n) ", &begin)); 

    std::cout << std::endl; 
    std::cout << "Escape from Moon Base 9" << std::endl; 
    std::cout << "-----------------------" << std::endl; 
    std::cout << std::endl; 
    std::cout << "The Story" << std::endl; 
    std::cout << "---------" << std::endl; 
    std::cout << "The year is 2518. You are a software engineer, and the only human, maintaining a team\n"
              << "of android miners on a moon base somewehre in the Alpha Centauri star system. Your employer\n" 
              << "is an instellar conglomerate called the CORPORATION." << std::endl; 
    std::cout << std::endl; 
    std::cout << "Everything was running smoothly until something went wrong with the latest system update,\n"
              << "and now all the androids, except one, have turned against humans." << std::endl;  
    std::cout << std::endl;
    std::cout << "The Goal: " << std::endl; 
    std::cout << "---------" << std::endl; 
    std::cout << "The moon base has three escape pods, but they will not work without an access code.\n" 
              << "You must find the single uninfected android, get the access code, and then find the correct\n"
              << "escape pod. Time is ticking! The virus also infected the base's life suport system,\n"
              << "and oxygen levels are dwindling. You only have 30 minutes to escape!"
              << std::endl; 
    std::cout << std::endl;
    std::cout << "Map Key" << std::endl; 
    std::cout << "---------" << std::endl; 
    std::cout << "+ wall" << std::endl; 
    std::cout << "* android" << std::endl; 
    std::cout << "P player" << std::endl; 
    std::cout << "E escape pod" << std::endl;
    std::cout << std::endl;
    menu->load(beginPlay); 
    
}

Game::~Game()
{
    delete base; 
    delete menu; 
    delete player; 
}
