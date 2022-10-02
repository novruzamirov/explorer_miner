//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Novruz Amirov
//---Student Number: 150200903
//--------------------------//

#include <iostream>
#include "Robot.h"
using namespace std;
class Crew
{
	friend class CommandCenter;

private:
	int maxExplorers;
	int maxMiners;
	int crewManufactureCost = 0;
	float crewMaintenanceCost = 0;
	int explorerCrewSize;
	int minerCrewSize;
	Explorer **ExplorerCrew;
	Miner **MinerCrew;

public:
	Crew(int, int, int, int);
	~Crew()
	{
		for (int i = 0; i < explorerCrewSize; i++)
		{
			delete ExplorerCrew[i];
		}
		delete ExplorerCrew;
		for (int i = 0; i < minerCrewSize; i++)
		{
			delete MinerCrew[i];
		}
		delete MinerCrew;
	}
	Robot *manufactureRobot(string);
	Robot *manufactureRobot();
	void initMovement();
	void updateDurability();
	void operator+=(Robot *);
	void operator-=(string);
	void showInfo() const;
	int getExplorerCrewSize() const
	{
		return explorerCrewSize;
	}
	int getMinerCrewSize() const
	{
		return minerCrewSize;
	}
	Miner **getMiners() const
	{
		return MinerCrew;
	}
	Explorer **getExplorers() const
	{
		return ExplorerCrew;
	}
	float getCrewMaintenanceCost() const
	{
		return crewMaintenanceCost;
	}
	void setCrewMaintenanceCost(float cost)
	{
		crewMaintenanceCost = cost;
	}
	int getCrewManufactureCost() const
	{
		return crewManufactureCost;
	}
	void setCrewManufactureCost(int cost)
	{
		crewManufactureCost = cost;
	}
};

class CommandCenter
{
private:
	const int neededSelenium;
	const float searchArea;
	const int seleniumWorth;
	int turnCount = 1;
	float totalCrewMaintenanceCost;
	float profit;

public:
	CommandCenter(const int, const int, const int);
	bool isGameEnded();
	void calculateProfit(const Crew &);
	void operator++();
	void showInfo() const;
	void setTurnCount(int count) // to set and get turnCount
	{
		turnCount = count;
	}
	int getTurnCount() const
	{
		return turnCount;
	}
};
