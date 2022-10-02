//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Novruz Amirov
//---Student Number: 150200903
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
//-------------Do Not Add Change Header Include Paths-------------/

#include <iostream>
using namespace std;
#include "Robot.h"

/*
****************
BEGIN: ROBOT CLASS FUNCTION DECLARATIONS 
****************
*/

int Robot::unqID = 1;

Robot::Robot(string type, float sp, int dur, int manufacture, float maintenance) : RobotType(type), manufactureCost(manufacture)
{
    speed = sp;
    durability = dur;
    maintenanceCost = maintenance;
    //remaining private att-s are setted:
    canMove = true;
}

void Robot::operator=(const Robot &inObj) // manufactureCost and RobotType cannot be changed even in = operator because they are const variables.
{
    RobotName = inObj.RobotName;
    speed = inObj.speed;
    durability = inObj.durability;
    maintenanceCost = inObj.maintenanceCost;
    canMove = inObj.canMove;
}

void Robot::showInfo() const
{
    cout << "Name: " << RobotName << endl;
    cout << "Type: " << RobotType << endl;
    cout << "Speed: " << speed << endl;
    cout << "Durability: " << durability << endl;
    cout << "ManufactureCost: " << manufactureCost << endl;
    cout << "MaintenanceCost: " << maintenanceCost << endl;
    cout << "Can Move: " << canMove << endl;
}

/*
****************
END: ROBOT CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: EXPLORER CLASS FUNCTION DECLARATIONS 
****************
*/

float Explorer::totalExploredArea = 0;
int Explorer::totalNumberOfSeleniumArea = 0;

Explorer::Explorer(string type, float sp, int dur) : Robot(type, 3000) // RobotType(type), manufactureCost(3000)
{
    speed = sp;
    durability = dur;
    maintenanceCost = 450 / speed;
    exploredArea = 0;

    RobotName = "exp-" + to_string(getUnqID());
    setUnqID(getUnqID() + 1);
}

bool Explorer::move()
{
    if (canMove)
    {
        canMove = false;
        return true;
    }
    else
        return false;
}

void Explorer::explore()
{
    int random_number = rand() % 101;
    if (random_number >= 40)
    {
        detectedSelenium = true;
        totalNumberOfSeleniumArea++;
    }
    else
    {
        detectedSelenium = false;
    }
    totalExploredArea += 1500;
    exploredArea = 1500;
}

void Explorer::operator=(const Explorer &inObj) // RobotType and manufactureCost cannot be changed due to being const variables.
{
    exploredArea = inObj.exploredArea;
    detectedSelenium = inObj.detectedSelenium;
    speed = inObj.speed;
    durability = inObj.durability;
    maintenanceCost = inObj.maintenanceCost;
    canMove = inObj.canMove;
}

void Explorer::showInfo() const
{
    Robot::showInfo();
    cout << "explored area: " << exploredArea << endl;
}

/*
****************
END: EXPLORER CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: MINER CLASS FUNCTION DECLARATIONS 
****************
*/

int Miner::totalGatheredSelenium = 0;

Miner::Miner(string type, float sp, int dur) : Robot(type, 5000) // RobotType(type), manufactureCost(5000)
{
    speed = sp;
    durability = dur;
    maintenanceCost = 750 / speed;
    gatheredSelenium = 0;

    RobotName = "mnr-" + to_string(getUnqID());
    setUnqID(getUnqID() + 1);
    // cout << "unqID is incremented: " << getUnqID() << endl;
}

void Miner::mine()
{
    int random_number = (rand() % 91) + 10; // to get random number between 10 and 100 bith inclusive
    int extracted_number_of_selenuims = random_number * 5;
    totalGatheredSelenium += extracted_number_of_selenuims;
    gatheredSelenium = extracted_number_of_selenuims;
}

bool Miner::move()
{
    Explorer test;
    if (canMove && test.totalNumberOfSeleniumArea)
    {
        test.totalNumberOfSeleniumArea -= 1;
        canMove = false;
        return true;
    }
    else
    {
        return false;
    }
}

void Miner::operator=(const Miner &inObj) // manufactureCost and RobotType can not be changed due to being const variables.
{
    gatheredSelenium = inObj.gatheredSelenium;
    speed = inObj.speed;
    durability = inObj.durability;
    maintenanceCost = inObj.maintenanceCost;
    canMove = inObj.canMove;
}

void Miner::showInfo() const
{
    Robot::showInfo();
    cout << "# of gathered selenium: " << gatheredSelenium << endl;
}

/*
****************
END: MINER CLASS FUNCTION DECLARATIONS 
****************
*/
