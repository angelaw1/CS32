#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(string assetDir)
	: GameWorld(assetDir)
{
	m_ticks = 0;
	m_ants0 = 0;
	m_ants1 = 0;
	m_ants2 = 0;
	m_ants3 = 0;
	m_ticks0 = 0;
	m_ticks1 = 0;
	m_ticks2 = 0;
	m_ticks3 = 0;
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}

int StudentWorld::init()
{
	Field f;
	string fieldFile = getFieldFilename();
	string error1;
	if (f.loadField(fieldFile, error1) != Field::LoadResult::load_success) {
		setError(fieldFile + " " + error1);
		return false;
	}
	fileNames = getFilenamesOfAntPrograms();

	Compiler *compilerForEntrant0, *compilerForEntrant1,
			 *compilerForEntrant2, *compilerForEntrant3;
	Anthill *ah0, *ah1, *ah2, *ah3;

	compilerForEntrant0 = new Compiler;
	compilerForEntrant1 = new Compiler;
	compilerForEntrant2 = new Compiler;
	compilerForEntrant3 = new Compiler;

	string error;
	if (fileNames.size() > 0 && !compilerForEntrant0->compile(fileNames[0], error))
	{
		delete compilerForEntrant0;
		setError(fileNames[0] + " " + error);
		return GWSTATUS_LEVEL_ERROR;
	}
	if (fileNames.size() > 1 && !compilerForEntrant1->compile(fileNames[1], error))
	{
		delete compilerForEntrant1;
		setError(fileNames[1] + " " + error);
		return GWSTATUS_LEVEL_ERROR;
	}
	if (fileNames.size() > 2 && !compilerForEntrant2->compile(fileNames[2], error))
	{
		delete compilerForEntrant2;
		setError(fileNames[2] + " " + error);
		return GWSTATUS_LEVEL_ERROR;
	}
	if (fileNames.size() > 3 && !compilerForEntrant3->compile(fileNames[3], error))
	{
		delete compilerForEntrant3;
		setError(fileNames[3] + " " + error);
		return GWSTATUS_LEVEL_ERROR;
	}

	for (int y = 0; y != VIEW_HEIGHT; y++) {
		for (int x = 0; x != VIEW_WIDTH; x++) {
			Field::FieldItem item = f.getContentsOf(x, y);
			if (item == Field::FieldItem::rock) {
				Pebble* newPebble = new Pebble(this, x, y);
				fieldArr[y][x].push_back(newPebble);
			}
			else if (item == Field::FieldItem::grasshopper) {
				BabyGrasshopper* newBabyGrasshopper = new BabyGrasshopper(this, x, y);
				fieldArr[y][x].push_back(newBabyGrasshopper);
			}
			else if (item == Field::FieldItem::food) {
				Food* newFood = new Food(this, x, y, 6000);
				fieldArr[y][x].push_back(newFood);
			}
			else if (item == Field::FieldItem::anthill0 ||
					 item == Field::FieldItem::anthill1 || 
					 item == Field::FieldItem::anthill2 || 
					 item == Field::FieldItem::anthill3) {
				{
					int colonyNum;
					if (fileNames.size() > 0 && item == Field::FieldItem::anthill0) {
						colonyNum = 0;
						ah0 = new Anthill(this, x, y, colonyNum, compilerForEntrant0);
						fieldArr[y][x].push_back(ah0);
					}
					else if (fileNames.size() > 1 && item == Field::FieldItem::anthill1) {
						colonyNum = 1;
						ah1 = new Anthill(this, x, y, colonyNum, compilerForEntrant1);
						fieldArr[y][x].push_back(ah1);
					}
					else if (fileNames.size() > 2 && item == Field::FieldItem::anthill2) {
						colonyNum = 2;
						ah2 = new Anthill(this, x, y, colonyNum, compilerForEntrant2);
						fieldArr[y][x].push_back(ah2);
					}
					else if (fileNames.size() > 3) {
						colonyNum = 3;
						ah3 = new Anthill(this, x, y, colonyNum, compilerForEntrant3);
						fieldArr[y][x].push_back(ah3);
					}
				}
			}
			else if (item == Field::FieldItem::water) {
				Water* newWater = new Water(this, x, y);
				fieldArr[y][x].push_back(newWater);
			}
			else if (item == Field::FieldItem::poison) {
				Poison* newPoison = new Poison(this, x, y);
				fieldArr[y][x].push_back(newPoison);
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
				if (!((*it)->isDead()) && !((*it)->hasMoved())) {
					(*it)->doSomething();
					// update actors that have moved in the array
					if (oldX != (*it)->getX() || oldY != (*it)->getY()) {
						(*it)->setMoveStatus(true);
						Actor* newptr = (*it);
						fieldArr[(*it)->getY()][(*it)->getX()].push_back(newptr);
						(*it) = nullptr;
						it = fieldArr[y][x].erase(it);
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
	if (m_ticks == 2000) {
		if (getCurrentWinner() != -1) {
			setWinner(fileNames[getCurrentWinner()].substr(0, fileNames[getCurrentWinner()].size() - 4));
			return GWSTATUS_PLAYER_WON;
		}
		return GWSTATUS_NO_WINNER;
	}
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

Actor* StudentWorld::getEdibleAt(int x, int y) const
{
	list<Actor*>::const_iterator it;
	it = fieldArr[y][x].begin();
	while (it != fieldArr[y][x].end()) {
		if ((*it)->canBeEaten())
			return *it;
		it++;
	}
	return nullptr;
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
				if ((*it)->isDead()) {
					EnergyHolder* insect = static_cast<EnergyHolder*>(*it);
					if (insect->becomesFoodUponDeath()) {
						constructFood(x, y, 100);
					}
					delete (*it);
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

int StudentWorld::unitsOfFoodAt(int x, int y)
{
	Actor* foodPtr = getEdibleAt(x, y);
	if (foodPtr != nullptr) {
		Food* food = static_cast<Food*>(foodPtr);
		return food->getEnergy();
	}
	return -1;
}

list<Actor*> StudentWorld::getList(int x, int y)
{
	return fieldArr[y][x];
}

string StudentWorld::updateDisplayText()
{
	int winner = getCurrentWinner();
	ostringstream oss;  // oss is a name of our choosing.
	int ticks = 2000 - m_ticks;
	oss.fill(' ');
	oss << setw(5) << ticks;
	string s = "Ticks:";
	s += oss.str();
	for (int i = 0; i != fileNames.size(); i++) {
		s += "  ";
		s += fileNames[i].substr(0, fileNames[i].size() - 4);
		if (winner == i)
			s += "*";
		s += ": ";
		ostringstream oss1;
		oss1.fill('0');
		oss1 << setw(2) << getAnts(i);
		s += oss1.str();
	}
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

void StudentWorld::constructFood(int x, int y, int amount)
{
	Actor* foodPtr = getEdibleAt(x, y);
	if (foodPtr != nullptr) {
			Food* food = static_cast<Food*>(foodPtr);
			food->updateEnergy(amount);
			return;
	}
	Food* newFood = new Food(this, x, y, amount);
	fieldArr[y][x].push_back(newFood);
}

void StudentWorld::constructAdultGrasshopper(int x, int y)
{
	Actor* newAdultGrasshopper = new AdultGrasshopper(this, x, y);
	fieldArr[y][x].push_back(newAdultGrasshopper);
}

int StudentWorld::eatFoodAt(int x, int y, int amount)
{
	Actor* foodPtr = getEdibleAt(x, y);
	if (foodPtr == nullptr)
		return 0;
	Food* food = static_cast<Food*>(foodPtr);
	int amountEaten = food->getEnergy();
	if (amountEaten > amount) {
		amountEaten = amount;
	}
	food->updateEnergy(-1 * amountEaten);
	return amountEaten;
}

int StudentWorld::numberOfEnemies(int x, int y, int colony, Actor* biter)
{
	list<Actor*>::iterator it = fieldArr[y][x].begin();
	int count = 0;
	while (it != fieldArr[y][x].end()) {
		if ((*it) != biter && (*it)->isEnemy(colony))
			count++;
		it++;
	}
	return count;
}

void StudentWorld::biteRandomEnemy(int x, int y, int colony, int sequence, Actor* biter, int bite)
{
	int totalEnemies = numberOfEnemies(x, y, colony, biter);
	list<Actor*>::iterator it = fieldArr[y][x].begin();
	int counter = 0;
	while (it != fieldArr[y][x].end()) {
		if ((*it) == biter || (*it)->isEnemy(colony))
			counter++;
		if (counter == sequence) {
			(*it)->getBitten(bite);
			break;
		}
		it++;
	}
	// (*it)->getBitten(bite);
	if ((*it)->canBiteBack() && randInt(1, 2) == 1)
		/*(*it)->getStudentWorldPtr()->*/biteRandomEnemy(x, y, 4, randInt(1, totalEnemies), (*it), (*it)->getBite());
}

void StudentWorld::constructAnt(int x, int y, int colonyNum, Compiler* program)
{
	int id;
	if (colonyNum == 0)
		id = IID_ANT_TYPE0;
	else if (colonyNum == 1)
		id = IID_ANT_TYPE1;
	else if (colonyNum == 2)
		id = IID_ANT_TYPE2;
	else
		id = IID_ANT_TYPE3;
	Actor* newAnt = new Ant(this, x, y, colonyNum, program, id);
	fieldArr[y][x].push_back(newAnt);
}

void StudentWorld::updateAnts(int colonyNum)
{
	if (colonyNum == 0) {
		m_ants0++;
		m_ticks0 = m_ticks;
	}
	else if (colonyNum == 1) {
		m_ants1++;
		m_ticks1 = m_ticks;
	}
	else if (colonyNum == 2) {
		m_ants2++;
		m_ticks2 = m_ticks;
	}
	else {
		m_ants3++;
		m_ticks3 = m_ticks;
	}
}

void StudentWorld::stunAllInsects(int x, int y)
{
	list<Actor*>::iterator it = fieldArr[y][x].begin();
	while (it != fieldArr[y][x].end()) {
		if ((*it)->canBeStunned() && !(*it)->alreadyStunned()) {
			(*it)->getStunned();
		}
		it++;
	}
}

void StudentWorld::poisonAllInsects(int x, int y)
{
	list<Actor*>::iterator it = fieldArr[y][x].begin();
	while (it != fieldArr[y][x].end()) {
		if ((*it)->canBePoisoned())
			(*it)->getPoisoned();
		it++;
	}
} 

void StudentWorld::addPheromone(int x, int y, int colony)
{
	list<Actor*>::iterator it;
	it = fieldArr[y][x].begin();
	while (it != fieldArr[y][x].end()) {
		if ((*it)->isPheromone(colony)) {
			Pheromone* pherPtr = static_cast<Pheromone*>(*it);
			pherPtr->updateEnergy(256);
			if (pherPtr->getEnergy() > 768)
				pherPtr->updateEnergy((-1 * pherPtr->getEnergy()) + 768);
			return;
		}
		it++;
	}
	Actor* newPher = new Pheromone(this, x, y, colony);
	fieldArr[y][x].push_back(newPher);
}

bool StudentWorld::isAnthillAt(int x, int y, int colony)
{
	list<Actor*>::iterator it;
	it = fieldArr[y][x].begin();
	while (it != fieldArr[y][x].end()) {
		if ((*it)->isAntHill(colony))
			return true;
		it++;
	}
	return false;
}

bool StudentWorld::isPheromoneAt(int x, int y, int colony)
{
	list<Actor*>::iterator it;
	it = fieldArr[y][x].begin();
	while (it != fieldArr[y][x].end()) {
		if ((*it)->isPheromone(0) || (*it)->isPheromone(1) ||
			(*it)->isPheromone(2) || (*it)->isPheromone(3))
			return true;
		it++;
	}
	return false;
}

bool StudentWorld::isDangerAt(int x, int y, int colony)
{
	list<Actor*>::iterator it;
	it = fieldArr[y][x].begin();
	while (it != fieldArr[y][x].end()) {
		if ((*it)->isDangerous(colony))
			return true;
		it++;
	}
	return false;
}

int StudentWorld::getTicks()
{
	return m_ticks;
}

int StudentWorld::getAnts(int colony)
{
	if (colony == 0)
		return m_ants0;
	else if (colony == 1)
		return m_ants1;
	else if (colony == 2)
		return m_ants2;
	else
		return m_ants3;
}

// returns the last tick when the anthill of this colony produced an ant
int StudentWorld::getColonyTick(int colony)
{
	if (colony == 0)
		return m_ticks0;
	else if (colony == 1)
		return m_ticks1;
	else if (colony == 2)
		return m_ticks2;
	else
		return m_ticks3;
}

int StudentWorld::getCurrentWinner()
{
	int winner = 0;
	bool areThereMultipleWinners = false;
	for (int i = 1; i < 4; i++) {
		if (getAnts(winner) <= getAnts(i)) {
			if (getAnts(winner) == getAnts(i)) {
				if (getColonyTick(winner) < getColonyTick(i)) {
					winner = i;
					areThereMultipleWinners = false;
				}
				else if (getColonyTick(winner) == getColonyTick(i))
					areThereMultipleWinners = true;
			}
			else {
				winner = i;
				areThereMultipleWinners = false;
			}
		}
	}
	if (!areThereMultipleWinners)
		return winner;
	return -1;
}