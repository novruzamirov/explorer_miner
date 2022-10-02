//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Novruz Amirov
//---Student Number: 150200903
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
//-------------Do Not Add Change Header Include Paths-------------//
#include "CommandCenter.h"
#include "Robot.h"
#include <iostream>
using namespace std;
/*
****************
BEGIN: CREW CLASS FUNCTION DECLARATIONS 
****************
*/

Crew::Crew(int mExplorers, int mMiners, int expCrewSize, int mnrCrewSize)
{
    if (mExplorers < 1 || mExplorers > 5)
        maxExplorers = 2;
    else
        maxExplorers = mExplorers;

    if (mMiners < 1 || mMiners > 5)
        maxMiners = 2;
    else
        maxMiners = mMiners;

    if (expCrewSize >= 0 && expCrewSize <= maxExplorers)
        explorerCrewSize = expCrewSize;
    else
        explorerCrewSize = maxExplorers;

    if (mnrCrewSize >= 0 && mnrCrewSize <= maxMiners)
        minerCrewSize = mnrCrewSize;
    else
        minerCrewSize = maxMiners;

    MinerCrew = new Miner *[maxMiners];
    ExplorerCrew = new Explorer *[maxExplorers];

    for (int i = 0; i < explorerCrewSize; i++)
    {
        Robot *a = manufactureRobot("explorer");
        Explorer *b = dynamic_cast<Explorer *>(a);
        ExplorerCrew[i] = b;
        setCrewManufactureCost(getCrewManufactureCost() + b->getManufactureCost());
    }

    for (int i = 0; i < minerCrewSize; i++)
    {
        Robot *a = manufactureRobot("miner");
        Miner *b = dynamic_cast<Miner *>(a);
        MinerCrew[i] = b;
        setCrewManufactureCost(getCrewManufactureCost() + b->getManufactureCost());
    }
}

Robot *Crew::manufactureRobot(string type)
{
    int durability;
    float speed;
    durability = (rand() % 5) + 1;
    string temp;
    speed = rand() / (float)RAND_MAX;

    if (type == "explorer")
    {
        speed = speed + 1.5;
        Explorer *newExplorer = new Explorer("explorer", speed, durability);
        newExplorer->setCanMove(true);
        return newExplorer;
    }

    else
    {
        speed = (speed / 2) + 1;
        Miner *newMiner = new Miner("miner", speed, durability);
        newMiner->setCanMove(true);
        return newMiner;
    }
}

Robot *Crew::manufactureRobot()
{
    int durability;
    float speed;
    durability = (rand() % 5) + 1;
    string temp = "";
    speed = rand() / (float)RAND_MAX;

    while (temp != "explorer" || temp != "miner")
    {
        cout << "Type:";
        cin >> temp;
        if (temp == "explorer" || temp == "miner")
            break;
    }
    if (temp == "explorer")
    {
        speed = speed + 1.5;
        Explorer *newExplorer = new Explorer("explorer", speed, durability);
        newExplorer->setCanMove(false);
        crewMaintenanceCost += newExplorer->getManufactureCost();
        return newExplorer;
    }
    else
    {
        speed = (speed / 2) + 1;
        Miner *newMiner = new Miner("miner", speed, durability);
        newMiner->setCanMove(false);
        crewMaintenanceCost += newMiner->getManufactureCost();
        return newMiner;
    }
}

void Crew::initMovement()
{
    for (int i = 0; i < explorerCrewSize; i++)
    {
        ExplorerCrew[i]->setCanMove(true);
    }
    for (int i = 0; i < minerCrewSize; i++)
    {
        MinerCrew[i]->setCanMove(true);
    }
}

void Crew::updateDurability()
{
    cout << "Explorer durability is being updated" << endl;
    for (int i = 0; i < explorerCrewSize; i++)
    {
        if (ExplorerCrew[i]->getDurability() != 1) // if different than 0, decrement by 1.
        {
            ExplorerCrew[i]->setDurability(ExplorerCrew[i]->getDurability() - 1);
        }
        else if (explorerCrewSize > 1) // if it is not only robot in that crew, delete it.
        {
            delete ExplorerCrew[i];
            for (int j = i; j < explorerCrewSize - 1; j++)
            {
                ExplorerCrew[j] = ExplorerCrew[j + 1];
            }
            explorerCrewSize--; // to delete one object of array, shift left by one, decrement crewSize, that will result in don't care in crewSize th element in array.
        }
        else
        {
            return; //do nothing
        }
    }
    cout << "Miner durability is being updated" << endl;
    for (int i = 0; i < minerCrewSize; i++)
    {
        if (MinerCrew[i]->getDurability() != 1) // if different than 0, decrement by 1.
        {
            MinerCrew[i]->setDurability(MinerCrew[i]->getDurability() - 1);
        }
        else if (minerCrewSize > 1) // if it is not only robot in that crew, delete it.
        {
            delete MinerCrew[i];
            for (int j = i; j < minerCrewSize - 1; j++)
            {
                MinerCrew[j] = MinerCrew[j + 1];
            }
            minerCrewSize--; // to delete one object of array, shift left by one, decrement crewSize, that will result in don't care in crewSize th element in array.
        }
        else
        {
            return; //do nothing
        }
    }
}

void Crew::operator+=(Robot *inObj)
{
    if (inObj->getType() == "miner" && minerCrewSize != maxMiners)
    {
        Miner *b = dynamic_cast<Miner *>(inObj);
        MinerCrew[minerCrewSize] = b;
        minerCrewSize++;
    }
    else if (inObj->getType() == "explorer" && explorerCrewSize != maxExplorers)
    {
        Explorer *b = dynamic_cast<Explorer *>(inObj);
        ExplorerCrew[explorerCrewSize] = b;
        explorerCrewSize++;
    }
    else
    {
        cout << "This robot cannot be added, check maximum size of the crew" << endl;
        crewMaintenanceCost -= inObj->getManufactureCost();
        delete inObj;
    }
}

void Crew::operator-=(string name)
{
    if (name[0] == 'e')
    {
        for (int i = 0; i < explorerCrewSize; i++)
        {
            if (ExplorerCrew[i]->getName() == name)
            {
                cout << name << ": Goodbye" << endl;
                if (explorerCrewSize != 1)
                {
                    delete ExplorerCrew[i];
                    for (int j = i; j < explorerCrewSize - 1; j++)
                    {
                        ExplorerCrew[j] = ExplorerCrew[j + 1];
                    }

                    explorerCrewSize--;
                    break;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < minerCrewSize; i++)
        {
            if (MinerCrew[i]->getName() == name)
            {
                cout << name << ": Goodbye" << endl;
                if (minerCrewSize != 1)
                {
                    delete MinerCrew[i];
                    for (int j = i; j < minerCrewSize - 1; j++)
                    {
                        MinerCrew[j] = MinerCrew[j + 1];
                    }
                    minerCrewSize--;
                    break;
                }
            }
        }
    }
}

void Crew::showInfo() const
{
    cout << "explorerCrew Size:" << explorerCrewSize << endl;
    cout << "minerCrew Size:" << minerCrewSize << endl;
    for (int i = 0; i < explorerCrewSize; i++)
    {
        ExplorerCrew[i]->showInfo();
    }
    for (int i = 0; i < minerCrewSize; i++)
    {
        MinerCrew[i]->showInfo();
    }
    cout << "Total manufacture cost: " << crewManufactureCost << endl;
    cout << "Total maintenance cost: " << crewMaintenanceCost << endl;
}

/*
****************
END: CREW CLASS FUNCTION DECLARATIONS 
****************
*/

/*
****************
BEGIN: COMMANDCENTER CLASS FUNCTION DECLARATIONS 
****************
*/

CommandCenter::CommandCenter(const int aim, const int area, const int worth) : neededSelenium(aim), searchArea(area), seleniumWorth(worth)
{
}

bool CommandCenter::isGameEnded()
{
    Explorer a("explorer", 12.12, 10);
    Miner b("miner", 12.12, 10);
    b.setUnqID(b.getUnqID() - 2);
    if (a.totalExploredArea >= searchArea)
    {
        if (profit > 0 && b.totalGatheredSelenium >= neededSelenium)
        {
            cout << "Area has been fully explored." << endl;
            cout << "Aim: " << neededSelenium << " selenium." << endl;
            cout << "Collected: " << b.totalGatheredSelenium << endl;
            cout << "Congrats!" << endl;
        }
        else
        {
            cout << "Mission Failed!" << endl;
        }

        return true;
    }
    else
    {
        return false;
    }
}

void CommandCenter::calculateProfit(const Crew &inObj)
{
    Miner b("miner", 12.12, 10);
    b.setUnqID(b.getUnqID() - 1);

    profit = (float(b.totalGatheredSelenium) * float(seleniumWorth)) - (float(inObj.crewMaintenanceCost) + float(inObj.crewManufactureCost));
    cout << "Profit:" << profit << endl;
    cout << "Expenses:" << float(inObj.crewMaintenanceCost) + float(inObj.crewManufactureCost) << endl;
    cout << "Selenium Revenue:" << float(b.totalGatheredSelenium) * float(seleniumWorth) << endl;
}

void CommandCenter::operator++()
{
    turnCount++;
}

void CommandCenter::showInfo() const
{
    Miner b("miner", 12.12, 10);
    Explorer e("explorer", 12.12, 10);
    b.setUnqID(b.getUnqID() - 2);
    cout << "Current turn: " << turnCount << endl;
    cout << "Aim: " << neededSelenium << " selenium." << endl;
    cout << "Collected: " << b.totalGatheredSelenium << endl;
    cout << "Total Search Area: " << searchArea << endl;
    cout << "Explored Area: " << e.totalExploredArea << endl;
    cout << "Currently, there are " << e.totalNumberOfSeleniumArea << " area/s that include selenium." << endl;
    if (e.totalNumberOfSeleniumArea > 0)
    {
        cout << "Mine these areas if miners have not finished their turn! If you cannot cope with mining, you can always add new miners!" << endl;
    }
}

/*
****************
END: COMMANDCENTER CLASS FUNCTION DECLARATIONS 
****************
*/