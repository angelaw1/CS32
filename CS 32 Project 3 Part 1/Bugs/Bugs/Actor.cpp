#include "Actor.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int startX, int startY, Direction dir, int depth, double size)
	: GraphObject(imageID, startX, startY, dir, depth, size)
{
	m_isAlive = true;
	m_hasMoved = false;
}

void Actor::setDead()
{
	m_isAlive = false;
}

bool Actor::isAlive()
{
	return m_isAlive;
}

bool Actor::blocksInsects()
{
	return false;
}

GraphObject::Direction Actor::getRandomDir()
{
	int dir = randInt(1, 4);
	if (dir == 1)
		return right;
	if (dir == 2)
		return up;
	if (dir == 3)
		return left;
	return down;
}

void Actor::setStudentWorldPtr(StudentWorld* ptr)
{
	m_studentWorldPtr = ptr;
}

StudentWorld* Actor::getStudentWorldPtr()
{
	return m_studentWorldPtr;
}

bool Actor::hasMoved()
{
	return m_hasMoved;
}

void Actor::setMoveStatus(bool statement)
{
	m_hasMoved = statement;
}

bool Pebble::blocksInsects()
{
	return true;
}

BabyGrasshopper::BabyGrasshopper(int x, int y) : Actor(IID_BABY_GRASSHOPPER, x, y, getRandomDir()) {
	m_hitPoints = 500;
	m_ticksLeft = 0;
	m_distanceToWalk = randInt(2, 10);
}

void BabyGrasshopper::doSomething() {
	m_hitPoints--;
	if (m_hitPoints == 0) {
		//add 100 units of food
		setVisible(false);
		setDead();
		return;
	}
	else if (m_ticksLeft != 0) {
		m_ticksLeft--;
		return;
	}
	// else if (m_hitPoints >= 1600) {
	//create new grasshopper
	//add 100 units of food
	// setVisible(false);
	// return;
	// }

	else if (m_distanceToWalk == 0) {
		setDirection(getRandomDir());
		m_distanceToWalk = randInt(2, 10);
	}
		int tempX;
		int tempY;
		if (getDirection() == up) {
			tempX = getX();
			tempY = getY() - 1;
		}
		else if (getDirection() == right) {
			tempX = getX() + 1;
			tempY = getY();
		}
		else if (getDirection() == down) {
			tempX = getX();
			tempY = getY() + 1;
		}
		else if (getDirection() == left) {
			tempX = getX() - 1;
			tempY = getY();
		}
		bool isTherePebble = getStudentWorldPtr()->isPebbleAtDestination(tempX, tempY);
		if (isTherePebble) {
			m_distanceToWalk = 0;
		}
		else {
			m_distanceToWalk--;
			moveTo(tempX, tempY);
		}
	m_ticksLeft = 2;
}

void BabyGrasshopper::minusHitPoint(int diff)
{
	m_hitPoints -= diff;
}

bool BabyGrasshopper::isSleeping()
{
	return m_ticksLeft != 0;
}

int BabyGrasshopper::getHitPoints()
{
	return m_hitPoints;
}

// void eat();
// void setTicksToSleep();
// void setDead();