#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(string assetDir)
	: GameWorld(assetDir)
{
	m_ticks = 0;
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}

int StudentWorld::init()
{
	Field f;
	string fieldFile = getFieldFilename();
	string error;
	if (f.loadField(fieldFile, error) != Field::LoadResult::load_success) {
		setError(fieldFile + " " + error);
		return false;
	}
	for (int y = 0; y != VIEW_HEIGHT; y++) {
		for (int x = 0; x != VIEW_WIDTH; x++) {
			Field::FieldItem item = f.getContentsOf(x, y);
			if (item == Field::FieldItem::rock) {
				Pebble* newPebble = new Pebble(x, y);
				newPebble->setStudentWorldPtr(this);
				fieldArr[y][x].push_back(newPebble);
			}
			else if (item == Field::FieldItem::grasshopper) {
				BabyGrasshopper* newBabyGrasshopper = new BabyGrasshopper(x, y);
				newBabyGrasshopper->setStudentWorldPtr(this);
				fieldArr[y][x].push_back(newBabyGrasshopper);
			}
		}
	}
	m_ticks = 0;
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	//when to change hasMoved back to false
	updateTickCount();
	for (int y = 0; y != VIEW_HEIGHT; y++) {
		for (int x = 0; x != VIEW_WIDTH; x++) {
			list<Actor*>::iterator it;
			it = fieldArr[y][x].begin();
			while (it != fieldArr[y][x].end()) {
				int oldX = (*it)->getX();
				int oldY = (*it)->getY();
				if ((*it)->isAlive() && !((*it)->hasMoved())) {
					(*it)->doSomething();
					// update actors that have moved in the array
					if (oldX != (*it)->getX() || oldY != (*it)->getY()) {
						(*it)->setMoveStatus(true);
						//list<Actor*>::iterator temp = it;
						//temp--;
						Actor* newptr = (*it);
						fieldArr[(*it)->getY()][(*it)->getX()].push_back(newptr);
						(*it) = nullptr;
						it = fieldArr[y][x].erase(it);
						//it = temp;
					}
					else
						it++;
				}
				else
					it++;
			}
		}
	}
	removeDeadSimulationObjects();
	setAllActorsToHasNotMoved();
	setGameStatText(updateDisplayText());
	if (m_ticks == 2000)
		return GWSTATUS_NO_WINNER;
	return GWSTATUS_CONTINUE_GAME;
} 

void StudentWorld::cleanUp()
{
	for (int y = 0; y != VIEW_HEIGHT; y++) {
		for (int x = 0; x != VIEW_WIDTH; x++) {
			list<Actor*>::iterator it;
			it = fieldArr[y][x].end();
			while (it != fieldArr[y][x].begin()) {
				it--;
				delete (*it);
				fieldArr[y][x].erase(it);
				it = fieldArr[y][x].end();
			}
		}
	}
}

void StudentWorld::updateTickCount()
{
	m_ticks++;
}

void StudentWorld::removeDeadSimulationObjects()
{
	for (int y = 0; y != VIEW_HEIGHT; y++) {
		for (int x = 0; x != VIEW_WIDTH; x++) {
			list<Actor*>::iterator it;
			it = fieldArr[y][x].end();
			while (it != fieldArr[y][x].begin()) {
				it--;
				if (!((*it)->isAlive())) {
					fieldArr[y][x].erase(it);
					it = fieldArr[y][x].end();
				}
			}
		}
	}
}

bool StudentWorld::isPebbleAtDestination(int x, int y)
{
	list<Actor*>::iterator it;
	it = fieldArr[y][x].end();
	while (it != fieldArr[y][x].begin()) {
		it--;
		if ((*it)->blocksInsects())
			return true;
	}
	return false;
}

/* list<Actor*>::iterator StudentWorld::getIterator(int x, int y)
{
	list<Actor*>::iterator it;
	it = fieldArr[y][x].end();
	return it;
} */

string StudentWorld::updateDisplayText()
{
	ostringstream oss;  // oss is a name of our choosing.
	oss << (2000 - m_ticks);
	string s = oss.str();
	return s;
}

void StudentWorld::setAllActorsToHasNotMoved()
{
	for (int y = 0; y != VIEW_HEIGHT; y++) {
		for (int x = 0; x != VIEW_WIDTH; x++) {
			list<Actor*>::iterator it;
			it = fieldArr[y][x].begin();
			while (it != fieldArr[y][x].end()) {
				(*it)->setMoveStatus(false);
				it++;
			}
		}
	}
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
