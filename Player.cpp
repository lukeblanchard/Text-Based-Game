/****************************************************************************
 ** Author: Lucas Blanchard
 ** Date: March 7, 2018
 ** Description: Implementation for Player class 
 ****************************************************************************/
#include "Player.hpp"

Player::Player(Space* location)
{
    currentSpace = location;
    menu = new Menu; 
    blaster = new Die(5); 
    forceField = new Die(3);
    supplies.push_back(4); //start with force field and blaster
    supplies.push_back(2); 
    numberItems = 2; 
    steps = 0; 
    blasterCount = 1; 
    forceFieldCount = 1; 
    medicineCount = 0;
    fuelCanisterCount = 0;
    health = 10; 
    gameOver = false; 
    lose = false; 
}

void Player::move(Space* newSpace)
{
    currentSpace = newSpace;
    steps += 1; 
    engageSpace(currentSpace->getContents()); 
    if(health <= 2 && medicineCount > 0) //use medicine if health <= 2
    {
        int medicineIndex; 
        health += 2; 
        medicineCount -= 1;
        std::cout << "You use a medicine pack to regain some strength." << std::endl; 
        for(int i = 0; i < numberItems; i++)
        {
            if(supplies[i] == 1)
            {
                medicineIndex = i; 
            }
        }
        supplies.erase(supplies.begin() + (medicineIndex)); //remove medicine from supplies
        numberItems--;
    }
}

void Player::engageSpace(int spaceType)
{
    bool flight = false; 
    BadDroid* droid; 
    menuBoolIO keepFighting;
    keepFighting.push_back(std::make_pair("Do you want to run from the evil android? (y/n) ", &flight)); 

    switch(spaceType)
    {
        case(0): 
            chooseSupplies(); 
            break;
        case(1):    //good droid 
            getPassCode(); 
            break;
        case(2): //bad droid
            droid = static_cast<BadDroid*>(currentSpace); 
            if(droid->getLifeStatus())
            {
                std::cout << "You encounter an evil android infected with the virus!" << std::endl; 
            }
            else
            {
                std::cout << "You already defeated this evil android." << std::endl;
            }
            while(droid->getLifeStatus() && !flight && health > 0) //fight until someone dies, or player wants to leave
            {
                combat();
                if(droid->getLifeStatus() && health > 0)
                {
                    menu->load(keepFighting); 
                }
            }
            break;
        case(3):
            engagePod(); 
            break; 
    }
}

void Player::defend(int attackForce)
{
    std::cout << "The android shoots!" << std::endl; 
    if(forceFieldCount > 0)
    {
        int defense = forceField->roll() * forceFieldCount; 
        if(attackForce > defense)
        {
            std::cout << "\tYou lose " << attackForce << " health points!" << std::endl; 
            health -= attackForce; 
            std::cout << "\tCurrent health: " << health << std::endl;
        }
        else
        {
            std::cout << "\tYour force field succesfully defends against the attack. No points lost!" << std::endl;
        }
    }
    else
    {
        std::cout << "\tYou lose " << attackForce << " health points!" << std::endl; 
        health -= attackForce;
    }

    if(health <= 2 && medicineCount > 0)
    {
        int medicineIndex; 
        health += 2; 
        medicineCount -= 1;
        std::cout << "You use a medicine pack to regain some strength." << std::endl; 
        for(int i = 0; i < numberItems; i++)
        {
            if(supplies[i] == 1)
            {
                medicineIndex = i; 
            }
        }
        supplies.erase(supplies.begin() + (medicineIndex)); 
        numberItems--;
    }
}

int Player::attack()
{
    if(blasterCount > 0)
    {
        std::cout << "You fire your blaster!" << std::endl; 
        return blaster->roll() * blasterCount; 
    }
    else
    {
        std::cout << "You have no blasters for the attack!" << std::endl; 
        return 0;
    }
}

void Player::combat()
{
    BadDroid* opponent = static_cast<BadDroid*>(currentSpace); 
    int attacker = rand() % 2; //random who attacks first, android or player
    int attackForce;
    if(opponent->getCharge() > 0)
    {
        if(attacker == 0) //player attacks first
        {
            attackForce = attack();  
            opponent->defend(attackForce); 
            if(opponent->getCharge() > 0)  
            {
                attackForce = opponent->interact();  
                defend(attackForce); 
                if(opponent->getCharge() <= 0)
                {
                    std::cout << "\tThe android shuts down." << std::endl;
                }
            }
            else
            {
                std::cout << "\tThe android shuts down." << std::endl;
            }
        }
        else //droid attacks first
        {
            attackForce = opponent->interact();  
            defend(attackForce); 
            if(health > 0)  
            {
                attackForce = attack();  
                opponent->defend(attackForce); 
                if(opponent->getCharge() <= 0)
                {
                    std::cout << "\tThe android shuts down." << std::endl;
                }
            }
        }
    }
    else
    {
        std::cout << "You already defeated this android." << std::endl;
    }
    opponent = nullptr; 
}

int Player::getHealth()
{
    return health; 
}

void Player::printSupplies()
{
    if(numberItems == 0)
    {
        std::cout << "You have no supplies." << std::endl;
    }
    else
    {
        std::cout << "Supplies: " << std::endl; 
        for(int i = 0; i < numberItems; i++)
        {
            switch(supplies[i])
            {
                case(1): 
                    std::cout << "\tMedicine" << std::endl;
                    break;
                case(2): 
                    std::cout << "\tBlaster" << std::endl; 
                    break; 
                case(3): 
                    std::cout << "\tFuel Canister" << std::endl; 
                    break; 
                case(4): 
                    std::cout << "\tForce Field" << std::endl; 
                    break; 
                case(5):
                    std::cout << "\tHard Drive" << std::endl; 
                    break; 
            }
        }
        std::cout << std::endl;
    }
}

void Player::chooseSupplies()
{
    OpenSpace* space = static_cast<OpenSpace*>(currentSpace); 
    int foundItem = space->interact(); 
    int leaveItem; 
    bool addItem; 
    
    menuBoolIO suppliesPrompt; 
    suppliesPrompt.push_back(std::make_pair("Do you want to add the item to your supplies? (y/n) ", &addItem)); 

    menuIntIO removeItem; 
    removeItem.push_back(std::make_pair(createItemsMenu(), &leaveItem)); 

    if(foundItem != 0)
    {
        menu->load(suppliesPrompt);
        if(addItem && numberItems < ITEMLIMIT)
        {
            supplies.push_back(foundItem);    
            space->setToEmpty(); 
            if(foundItem == 1) 
            {
                medicineCount += 1; 
            }
            else if(foundItem == 2)
            {
                blasterCount += 1;  
            }
            else if(foundItem == 3)
            {
                fuelCanisterCount += 1;
            }
            else if(foundItem == 4)
            {
                forceFieldCount += 1;  
            }
            numberItems++;
        }
        else if(addItem && numberItems == ITEMLIMIT) //need to leave an item behind, limit is 4 items
        {
            std::cout << "Your supplies are at capacity. You must choose an item to leave." << std::endl;
            menu->load(removeItem, 1, numberItems+1); 
            if(leaveItem != numberItems+1)
            {
                switch(supplies[leaveItem - 1]) //must adjust count of items, if one of those items is left, and then set space to left item
                {
                    case(1):
                        medicineCount -= 1; 
                        space->setObject(5); 
                        break; 
                    case(2): 
                        blasterCount -= 1; 
                        space->setObject(7); 
                        break; 
                    case(3):
                        fuelCanisterCount -= 1; 
                        space->setObject(8); 
                        break; 
                    case(4):
                        forceFieldCount -= 1; 
                        space->setObject(9); 
                        break; 
                }
                supplies.erase(supplies.begin() + (leaveItem - 1)); 
                supplies.push_back(foundItem); 
            }
        }
    }
}

std::string Player::createItemsMenu()
{
    std::string removeItemPrompt = ""; 

    for(int i = 0; i < numberItems; i++)
    {
            removeItemPrompt += std::to_string(i + 1); 
            switch(supplies[i])
            {
                case(1): 
                    removeItemPrompt += " Medicine\n"; 
                    break;
                case(2): 
                    removeItemPrompt += " Blaster\n"; 
                    break; 
                case(3): 
                    removeItemPrompt += " Fuel Canister\n"; 
                    break; 
                case(4): 
                    removeItemPrompt += " Force Field\n"; 
                    break; 
                case(5):
                    removeItemPrompt += " Hard Drive\n"; 
                    break; 
            }
    }

    removeItemPrompt += std::to_string(numberItems+1); 
    removeItemPrompt += " Do not change supplies.\n"; 
    removeItemPrompt += "Please enter your choice as a number: "; 

    return removeItemPrompt;
}

Space* Player::getCurrentLocation()
{
    return currentSpace;
}

int Player::getSteps()
{
    return steps;
}

void Player::printStats()
{
    std::cout << std::endl;     
    std::cout << "Player Stats" << std::endl; 
    std::cout << "------------" << std::endl;
    std::cout << "Health: " << health << std::endl; 
    std::cout << "Minutes Remaining: " << STEPLIMIT - steps << std::endl;
    printSupplies(); 
}

void Player::getPassCode()
{
    GoodDroid* droid = static_cast<GoodDroid*>(currentSpace); 
    int leaveItem;
    menuIntIO removeItem; 
    removeItem.push_back(std::make_pair(createItemsMenu(), &leaveItem)); 
    
    droid->interact(); 

    if(numberItems == ITEMLIMIT && droid->getAlive())
    {
        std::cout << "Your supplies are at capacity. You must choose an item to leave." << std::endl;
        menu->load(removeItem, 1, numberItems); 
        switch(supplies[leaveItem - 1])
        {
            case(1):
                medicineCount -= 1; 
                break; 
            case(2): 
                blasterCount -= 1; 
                break; 
            case(3):
                fuelCanisterCount -= 1; 
                break; 
            case(4):
                forceFieldCount -= 1; 
                break; 
        }
        supplies.erase(supplies.begin() + (leaveItem - 1)); 
        supplies.push_back(5); //add hard drive to supplies 
        droid->setAlive(false); 
        std::cout << "After giving you the drive, the android dies!" << std::endl;
    }
    else if(numberItems < ITEMLIMIT && droid->getAlive())
    {
        supplies.push_back(5); //add hard drive to supplies
        numberItems++; //only increase, if supplies were not full
        droid->setAlive(false); 
        std::cout << "After giving you the drive, the android dies!" << std::endl;
    }
}

void Player::engagePod()
{
    EscapePod* pod = static_cast<EscapePod*>(currentSpace); 
    bool haveFuel = fuelCanisterCount > 0; 
    int escape = pod->interactWrapper(haveFuel); 
    if(escape == 1)
    {
        std::cout << "You escape the base and the pod sets course for CORPORATION headquarters!" << std::endl; 
        if(std::find(supplies.begin(), supplies.end(), 5) == supplies.end()) //if player does not have hard drive
        {
            std::cout << "But you left behind the drive containing vital information about the virus!" << std::endl;  
            std::cout << "You cannot change the escape pod's course. In just one hour you will arrive at headquarters" << std::endl; 
            std::cout << "where the CORPORATION police will put you on the next prison ship to Planet Inferno." << std::endl; 
            std::cout << "Good luck fighting the sand worms!" << std::endl; 
            lose = true; 
            gameOver = true; 
        }
        else
        {
            lose = false; 
            gameOver = true; 
        }
    }
}

bool Player::getGameOver()
{
    return gameOver;
}

bool Player::getLose()
{
    return lose;
}

Player::~Player()
{
    delete menu;
    delete blaster;
    delete forceField;
}
