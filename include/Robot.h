//--- 2021-2022 Summer Object Oriented Programing Assignment 2 ---//
//--------------------------//
//---Name & Surname: Novruz Amirov
//---Student Number: 150200903
//--------------------------//
#include <iostream>
#ifndef _H
#define _H
using namespace std;
class Robot
{
private:
	static int unqID; //unqID was made private STATIC member of class, and getter and setter function was constructed for that.

protected:
	string RobotName;
	const string RobotType; // can not be changed after instantiatinng an object from this class, thus it must be const.
	float speed;
	int durability;
	const int manufactureCost; // can not be changed after instantiatinng an object from this class, thus it must be const.
	float maintenanceCost;
	bool canMove;

public:
	Robot(string, float, int, int, float);											  // constructor of Robot class.
	Robot(const string type, const int cost) : RobotType(type), manufactureCost(cost) //to initialize const members of Robot
	{
	}
	void operator=(const Robot &); // overloading assign operator to copy Robot's att-s to another Robot.
	virtual void showInfo() const; // printing the att-s of Robot. // to use dynamic_cast, virtual keyword is used here.
	void setUnqID(int id)		   // setter method for static private variable: // must be inline
	{
		unqID = id;
	}
	int getUnqID() const // getter method for static private variable: // must be inline // must be CONST, like other getter methods.
	{
		return unqID;
	}
	void setCanMove(bool move)
	{
		canMove = move; // in order to change canMove in manufactureRobot() method in crew.
	}
	int getDurability() const // to set and get durabilities of robot
	{
		return durability;
	}
	void setDurability(int dur)
	{
		durability = dur;
	}
	string getType() const // to get RobotType
	{
		return RobotType;
	}
	string getName() const // to get RobotName
	{
		return RobotName;
	}
	int getManufactureCost() const
	{
		return manufactureCost;
	}
	virtual ~Robot(){}; //deconstructor
};

class Explorer : public Robot // Explorer class publicly inherits from Robot class
{
	friend class Miner;			// Miner class can directly access to the private member variables of the Explorer class.
	friend class CommandCenter; // CommandCenter can directly access to the private member variables of the Explorer class.

private:
	static float totalExploredArea; // totalExploredArea and totalNumberOfSeleniumArea does not depend on an instance of this class.
	static int totalNumberOfSeleniumArea;
	float exploredArea;
	bool detectedSelenium = false;

public:
	Explorer() : Robot("explorer", 3000)
	{
	}
	Explorer(string, float, int);	  // constructor which takes inherited variables as arguments.
	bool move();					  // returns a boolean variable that represents allowance of Robot to be moved for current game turn.
	void explore();					  // to explore areas for finding a selenium on the ground
	void operator=(const Explorer &); // assigning operator to copy Explorer's att-s to another one.
	void showInfo() const;			  // to show the values of member variables of Explorer including inherited ones.
	//getters and setters for static private variables: // must be inline functions.
	void setTotalExploredArea(float area)
	{
		totalExploredArea = area;
	}
	float getTotalExploredArea() const
	{
		return totalExploredArea;
	}
	void setTotalNumberOfSeleniumArea(int area)
	{
		totalNumberOfSeleniumArea = area;
	}
	int getTotalNumberOfSeleniumArea() const
	{
		return totalNumberOfSeleniumArea;
	}
	float getMaintenanceCost() const
	{
		return maintenanceCost;
	}
	bool getDetectedSelenium() const
	{
		return detectedSelenium;
	}
};

class Miner : public Robot // Miner class publicly inherits from Robot class
{
	friend class CommandCenter;

private:
	static int totalGatheredSelenium; // does not depend on instance of this class, thus it is static variable.
	int gatheredSelenium;

public:
	Miner() : Robot("miner", 5000)
	{
	}
	Miner(string, float, int);			   // constructor which takes inherited variables as arguments.
	void mine();						   // to mine the areas with seleniums.
	bool move();						   // returns a boolean variable that represents the allowance of robot to be moved for current game turn.
	void operator=(const Miner &inObject); // overloading assign operator to copy Miner's att-s to another one.
	void showInfo() const;				   // to show the values of member variables of the Miner including inherited ones.
	// getters and setters for static private variable:
	void setTotalGatheredSelenium(int total)
	{
		totalGatheredSelenium = total;
	}
	int getTotalGatheredSelenium() const
	{
		return totalGatheredSelenium;
	}
	float getMaintenanceCost() const
	{
		return maintenanceCost;
	}
};

#endif
