#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
	Actor(int imageID, int startX, int startY, Direction dir = right, int depth = 0, double size = 0.25);
	// virtual ~Actor();
	void setDead();
	virtual void doSomething() = 0;
	bool isAlive();
	virtual bool blocksInsects();
	Direction getRandomDir();
	void setStudentWorldPtr(StudentWorld* ptr);
	StudentWorld* getStudentWorldPtr();
	bool hasMoved();
	void setMoveStatus(bool statement);
private:
	StudentWorld* m_studentWorldPtr;
	bool m_isAlive;
	bool m_hasMoved;
};

class Pebble : public Actor {
public:
	Pebble(int x, int y) : Actor(IID_ROCK, x, y, right, 1) {}
	virtual void doSomething() {}
	virtual bool blocksInsects();
};

class BabyGrasshopper : public Actor {
public:
	BabyGrasshopper(int x, int y);
	virtual void doSomething();
	void minusHitPoint(int diff);
	int getHitPoints();
	bool isSleeping();
	// void eat();
	// void setTicksToSleep();
	// void setDead();
private:
	int m_hitPoints;
	int m_ticksLeft;
	int m_distanceToWalk;
};

#endif // ACTOR_H_