#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Field.h"
#include <string>
#include <list>
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

	void updateTickCount();

	void removeDeadSimulationObjects();

	string updateDisplayText();

	bool isPebbleAtDestination(int x, int y);

	void setAllActorsToHasNotMoved();

	// list<Actor*>::iterator getIterator(int x, int y);

private:
	list<Actor*> fieldArr[64][64];
	int m_ticks;
};

#endif // STUDENTWORLD_H_
