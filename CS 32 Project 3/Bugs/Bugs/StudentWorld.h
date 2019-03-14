#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Field.h"
#include <string>
#include <list>
#include "Compiler.h"
using namespace std;

class Actor;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(string assetDir);
	virtual ~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	Actor* getEdibleAt(int x, int y) const;
	void updateTickCount();
	void removeDeadSimulationObjects();
	string updateDisplayText();
	bool isPebbleAtDestination(int x, int y);
	int unitsOfFoodAt(int x, int y);
	void setAllActorsToHasNotMoved();
	list<Actor*> getList(int x, int y);
	void constructFood(int x, int y, int amount);
	void constructAdultGrasshopper(int x, int y);
	int eatFoodAt(int x, int y, int amount);
	int numberOfEnemies(int x, int y, int colony, Actor* biter);
	void biteRandomEnemy(int x, int y, int colony, int sequence, Actor* biter, int bite);
	void constructAnt(int x, int y, int colonyNum, Compiler* program);
	void updateAnts(int colonyNum);
	void stunAllInsects(int x, int y);
	void poisonAllInsects(int x, int y);
	void addPheromone(int x, int y, int colony);
	bool isAnthillAt(int x, int y, int colony);
	bool isPheromoneAt(int x, int y, int colony);
	bool isDangerAt(int x, int y, int colony);
	int getTicks();
	int getAnts(int colony);
	int getColonyTick(int colony);
	int getCurrentWinner();
private:
	list<Actor*> fieldArr[64][64];
	int m_ticks;
	int m_ants0;
	int m_ants1;
	int m_ants2;
	int m_ants3;
	int m_ticks0;
	int m_ticks1;
	int m_ticks2;
	int m_ticks3;
	vector<string> fileNames;
};

#endif // STUDENTWORLD_H_
