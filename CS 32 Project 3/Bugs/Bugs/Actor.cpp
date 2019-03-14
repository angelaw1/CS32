#include "Actor.h"
#include <algorithm>
#include <cmath>


////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////ACTOR IMPLEMENTATION//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Actor::Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, int depth)
	: GraphObject(imageID, startX, startY, dir, depth)
{
	m_isAlive = true;
	m_hasMoved = false;
	m_studentWorldPtr = sw;
}

bool Actor::isDead() const
{
	return false;
}

bool Actor::blocksInsects() const
{
	return false;
}
// Cause this actor to be be bitten, suffering an amount of damage.
void Actor::getBitten(int amt)
{}

// Cause this actor to be be poisoned.
void Actor::getPoisoned()
{}

// Cause this actor to be be stunned.
void Actor::getStunned()
{}

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

bool Actor::canBeEaten() const
{
	return false;
}

bool Actor::canBeBitten()
{
	return false;
}

bool Actor::alreadyStunned()
{
	return true;
}

void Actor::setStunnedTo(bool statement) {}

bool Actor::canBeStunned()
{
	return false;
}

bool Actor::canBePoisoned()
{
	return canBeStunned();
}

int Actor::getBite() {
	return 0;
}

bool Actor::canBiteBack()
{
	return false;
}

bool Actor::isPheromone(int colony) const
{
	return false;
}

bool Actor::isEnemy(int colony) const
{
	return false;
}

bool Actor::isDangerous(int colony) const
{
	return false;
}

bool Actor::isAntHill(int colony) const
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////ENERGYHOLDER IMPLEMENTATION///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

EnergyHolder::EnergyHolder(StudentWorld* sw, int startX, int startY, Direction startDir, int energy, int imageID, int depth)
	: Actor(sw, imageID, startX, startY, startDir, 1)
{
	m_energy = energy;
	m_food = 0;
}

bool EnergyHolder::isDead() const
{
	return m_energy <= 0;
}

int EnergyHolder::getEnergy()
{
	return m_energy;
}

void EnergyHolder::updateEnergy(int amt)
{
	m_energy += amt;
}

void EnergyHolder::addFood(int amt)
{
	getStudentWorldPtr()->constructFood(getX(), getY(), amt);
}

int EnergyHolder::pickupFood(int amt)
{
	int amountChanged;
	amountChanged = getStudentWorldPtr()->eatFoodAt(getX(), getY(), amt);
	m_food += amountChanged;
	return amountChanged;
}
int EnergyHolder::pickupAndEatFood(int amt)
{
	int amountChanged;
	amountChanged = getStudentWorldPtr()->eatFoodAt(getX(), getY(), amt);
	updateEnergy(amountChanged);
	return amountChanged;
}
bool EnergyHolder::becomesFoodUponDeath() const
{
	return false;
}

void EnergyHolder::setDead()
{
	m_energy = 0;
}

int EnergyHolder::getFood()
{
	return m_food;
}

void EnergyHolder::updateFood(int amt)
{
	m_food += amt;
}

////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////INSECT IMPLEMENTATION/////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Insect::Insect(StudentWorld* sw, int imageID, int x, int y, int energy)
	: EnergyHolder(sw, x, y, getRandomDir(), energy, imageID, 1)
{
	m_ticksLeft = 0;
	m_alreadyStunned = false;
}
void Insect::changeTicksBy(int diff)
{
	m_ticksLeft += diff;
}

bool Insect::isSleeping()
{
	return m_ticksLeft != 0;
}

bool Insect::canBeBitten()
{
	return true;
}

bool Insect::alreadyStunned()
{
	return m_alreadyStunned;
}

void Insect::setStunnedTo(bool statement)
{
	m_alreadyStunned = statement;
}

void Insect::getBitten(int amt)
{
	updateEnergy(-1 * amt);
	if (isDead()) {
		setVisible(false);
	}
}

void Insect::getPoisoned()
{
	updateEnergy(-150);
	if (isDead()) {
		setVisible(false);
	}
}

void Insect::getStunned()
{
	changeTicksBy(2);
	setStunnedTo(true);
}

bool Insect::isEnemy(int colony)
{
	return false;
}

bool Insect::becomesFoodUponDeath() const
{
	return true;
}
// Set x,y to the coordinates of the spot one step in front of this insect.
void Insect::getXYInFrontOfMe(int &x, int &y) const
{
	if (getDirection() == up) {
		x = getX();
		y = getY() - 1;
	}
	else if (getDirection() == right) {
		x = getX() + 1;
		y = getY();
	}
	else if (getDirection() == down) {
		x = getX();
		y = getY() + 1;
	}
	else if (getDirection() == left) {
		x = getX() - 1;
		y = getY();
	}
}

bool Insect::moveForwardIfPossible()
{
	int tempX = 0;
	int tempY = 0;
	getXYInFrontOfMe(tempX, tempY);
	bool isTherePebble = getStudentWorldPtr()->isPebbleAtDestination(tempX, tempY);
	if (isTherePebble) {
		return false;
	}
	else {
		moveTo(tempX, tempY);
		setStunnedTo(false);
		return true;
	}
}

bool Insect::canBeStunned()
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////TRIGGERABLEACTOR IMPLEMENTATION/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

TriggerableActor::TriggerableActor(StudentWorld* sw, int x, int y, int imageID)
	: Actor(sw, imageID, x, y, right, 2)
{}

bool TriggerableActor::isDangerous(int colony) const
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////ANT IMPLEMENTATION///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Ant::Ant(StudentWorld* sw, int startX, int startY, int colony, Compiler* program, int imageID)
	: Insect(sw, imageID, startX, startY, 1500)
{
	m_colonyNum = colony;
	m_instructionCounter = 0;
	m_antCompiler = program;
	m_lastRandNum = 0;
	m_oldX = startX;
	m_oldY = startY;
	m_bitten = false;
}
void Ant::doSomething()
{
	updateEnergy(-1);
	if (isDead()) {
		setVisible(false);
		return;
	}
	else if (isSleeping()) {
		changeTicksBy(-1);
		return;
	}

	if (!simpleInterpreter(m_antCompiler)) {
		setDead();
		setVisible(false);
		return;
	}
}

void Ant::getBitten(int amt)
{
	Insect::getBitten(amt);
	string current = "";
	current += getX();
	current += ", ";
	current += getY();
	m_bitten = true;
}

bool Ant::isEnemy(int colony) const
{
	return m_colonyNum != colony;
}

bool Ant::simpleInterpreter(Compiler* c)
{
	int commandsRan = 0;
	while (commandsRan < 10) {
		Compiler::Command cmd;
		if (!(c->getCommand(m_instructionCounter, cmd)))
			return false;
		else if (cmd.opcode == Compiler::moveForward) {
			m_oldX = getX();
			m_oldY = getY();
			string coord = "";
			coord += getX();
			coord += ", ";
			coord += getY();
			bool moved = moveForwardIfPossible();
			if (moved) {
				m_notBlocked.push_back(coord);
				m_bitten = false;
			}
			else
				m_blocked.push_back(coord);
			m_instructionCounter++;
			return true;
		}
		else if (cmd.opcode == Compiler::eatFood) {
			int amountEaten = getFood();
			if (getFood() > 100)
				amountEaten = 100;
			updateEnergy(amountEaten);
			addFood(-1 * amountEaten);
			m_instructionCounter++;
			return true;
		}
		else if (cmd.opcode == Compiler::dropFood) {
			int food = getFood();
			if (food > 0) {
				getStudentWorldPtr()->constructFood(getX(), getY(), food);
				updateFood(-1 * food);
			}
			m_instructionCounter++;
			return true;
		}
		else if (cmd.opcode == Compiler::bite) {
			int totalEnemies = getStudentWorldPtr()->numberOfEnemies(getX(), getY(), m_colonyNum, this);
			if (totalEnemies > 0)
				getStudentWorldPtr()->biteRandomEnemy(getX(), getY(), m_colonyNum, randInt(1, totalEnemies), this, 15);
			m_instructionCounter++;
			return true;
		}
		else if (cmd.opcode == Compiler::pickupFood) {
			int amtOfFood = getStudentWorldPtr()->unitsOfFoodAt(getX(), getY());
			if (amtOfFood > 0 && getFood() < 1800) {
				if (1800 - getFood() > amtOfFood) {
					amtOfFood = 1800 - getFood();
				}
				if (amtOfFood > 400)
					amtOfFood = 400;
				getStudentWorldPtr()->eatFoodAt(getX(), getY(), amtOfFood);
				addFood(amtOfFood);
			}
			m_instructionCounter++;
			return true;
		}
		else if (cmd.opcode == Compiler::emitPheromone) {
			getStudentWorldPtr()->addPheromone(getX(), getY(), m_colonyNum);
			m_instructionCounter++;
			return true;
		}
		else if (cmd.opcode == Compiler::faceRandomDirection) {
			setDirection(getRandomDir());
			m_instructionCounter++;
			return true;
		}
		else if (cmd.opcode == Compiler::rotateClockwise) {
			if (getDirection() == right)
				setDirection(down);
			else if (getDirection() == down)
				setDirection(left);
			else if (getDirection() == left)
				setDirection(up);
			else
				setDirection(right);
			m_instructionCounter++;
			return true;
		}
		else if (cmd.opcode == Compiler::rotateCounterClockwise) {
			if (getDirection() == right)
				setDirection(up);
			else if (getDirection() == up)
				setDirection(left);
			else if (getDirection() == left)
				setDirection(down);
			else
				setDirection(right);
			m_instructionCounter++;
			return true;
		}
		else if (cmd.opcode == Compiler::generateRandomNumber) {
			if (cmd.operand1 == "0")
				m_lastRandNum = 0;
			else
				m_lastRandNum = randInt(1, stoi(cmd.operand1) - 1);
			m_instructionCounter++;
			commandsRan++;
			break;
		}
		else if (cmd.opcode == Compiler::goto_command) {
			m_instructionCounter = stoi(cmd.operand1);
			commandsRan++;
			break;
		}
		else if (cmd.opcode == Compiler::if_command) {
			bool statement = false;
			if (cmd.operand1 == "0") {
				int x;
				int y;
				getXYInFrontOfMe(x, y);
				if (getStudentWorldPtr()->isDangerAt(x, y, m_colonyNum))
					statement = true;
			}
			else if (cmd.operand1 == "1") {
				if (getStudentWorldPtr()->isPheromoneAt(getX(), getY(), m_colonyNum))
					statement = true;
			}
			else if (cmd.operand1 == "2") {
				string current = "";
				current += getX();
				current += ", ";
				current += getY();
				if (m_bitten)
					statement = true;
			}
			else if (cmd.operand1 == "3") {
				if (getFood() > 0)
					statement = true;
			}
			else if (cmd.operand1 == "4") {
				if (getEnergy() <= 25)
					statement = true;
			}
			else if (cmd.operand1 == "5") {
				if (getStudentWorldPtr()->isAnthillAt(getX(), getY(), m_colonyNum))
					statement = true;
			}
			else if (cmd.operand1 == "6") {
				if (getStudentWorldPtr()->unitsOfFoodAt(getX(), getY()) > 0) {
					statement = true;
				}
			}
			else if (cmd.operand1 == "7") {
				if (getStudentWorldPtr()->numberOfEnemies(getX(), getY(), m_colonyNum, this) > 0)
					statement = true;
			}
			else if (cmd.operand1 == "8") {
				string last = "";
				last += m_oldX;
				last += ", ";
				last += m_oldY;
				if (!m_notBlocked.empty() && m_notBlocked[m_notBlocked.size() - 1] == last)
					statement = true;
			}
			else if (cmd.operand1 == "9") {
				if (m_lastRandNum == 0)
					statement = true;
			}
			if (statement)
				m_instructionCounter = stoi(cmd.operand2);
			else
				m_instructionCounter++;
			commandsRan++;
		}
	}
	return true;
}

bool Ant::isDangerous(int colony)
{
	return m_colonyNum != colony;
}

////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////PEBBLE IMPLEMENTATION//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Pebble::Pebble(StudentWorld* sw, int x, int y)
	: Actor(sw, IID_ROCK, x, y, right, 1)
{}

void Pebble::doSomething() {}

bool Pebble::blocksInsects() const
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////FOOD IMPLEMENTATION//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Food::Food(StudentWorld* sw, int x, int y, int units)
	: EnergyHolder(sw, x, y, right, units, IID_FOOD, 2)
{
	m_units = units;
}

void Food::doSomething() {}

bool Food::canBeEaten() const
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////PHEROMONE IMPLEMENTATION////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Pheromone::Pheromone(StudentWorld* sw, int x, int y, int colony)
	: EnergyHolder(sw, x, y, right, 256, colony + IID_PHEROMONE_TYPE0, 2)
{
	m_colony = colony;
}

void Pheromone::doSomething()
{
	updateEnergy(-1);
	if (isDead())
	{
		setVisible(false);
	}
}

bool Pheromone::isPheromone(int colony) const
{
	return m_colony == colony;
}

////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////ANTHILL IMPLEMENTATION/////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Anthill::Anthill(StudentWorld* sw, int x, int y, int colonyNum, Compiler* program)
	: EnergyHolder(sw, x, y, right, 8999, IID_ANT_HILL, 2)
{
	m_colonyNum = colonyNum;
	m_program = program;
}

Anthill::~Anthill()
{
	delete m_program;
}

void Anthill::doSomething()
{
	updateEnergy(-1);
	if (getEnergy() < 1) {
		setDead();
		setVisible(false);
		return;
	}
	else if (getStudentWorldPtr()->unitsOfFoodAt(getX(), getY()) > 0) {
		int food = getStudentWorldPtr()->unitsOfFoodAt(getX(), getY());
		food = getStudentWorldPtr()->eatFoodAt(getX(), getY(), food);
		updateEnergy(food);
		return;
	}
	else if (getEnergy() >= 2000) {
		getStudentWorldPtr()->constructAnt(getX(), getY(), m_colonyNum, m_program);
		updateEnergy(-1500);
		getStudentWorldPtr()->updateAnts(m_colonyNum);
	}
}

bool Anthill::canBeBitten()
{
	return false;
}

bool Anthill::isAntHill(int colony) const
{
	return m_colonyNum == colony;
}

////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////WATER IMPLEMENTATION//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Water::Water(StudentWorld* sw, int x, int y)
	: TriggerableActor(sw, x, y, IID_WATER_POOL)
{}

void Water::doSomething()
{
	getStudentWorldPtr()->stunAllInsects(getX(), getY());
}

////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////POISON IMPLEMENTATION//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Poison::Poison(StudentWorld* sw, int x, int y)
	: TriggerableActor(sw, x, y, IID_POISON)
{}

void Poison::doSomething()
{
	getStudentWorldPtr()->poisonAllInsects(getX(), getY());
}

////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////GRASSHOPPER IMPLEMENTATION////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Grasshopper::Grasshopper(StudentWorld* sw, int imageID, int x, int y, int energy)
	: Insect(sw, imageID, x, y, energy)
{
	m_distanceToWalk = randInt(2, 10);
}

void Grasshopper::setDistanceToWalkTo(int distance)
{
	m_distanceToWalk = distance;
}

int Grasshopper::getDistanceToWalk()
{
	return m_distanceToWalk;
}

bool Grasshopper::isDangerous(int colony)
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////BABY GRASSHOPPER IMPLEMENTATION/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

BabyGrasshopper::BabyGrasshopper(StudentWorld* sw, int x, int y)
	: Grasshopper(sw, IID_BABY_GRASSHOPPER, x, y, 500)
{}

void BabyGrasshopper::doSomething() {
	updateEnergy(-1);
	if (isDead()) {
		setVisible(false);
		return;
	}
	else if (isSleeping()) {
		changeTicksBy(-1);
		return;
	}

	if (getEnergy() >= 1600) {
		getStudentWorldPtr()->constructAdultGrasshopper(getX(), getY());
		setDead();
		setVisible(false);
		return;
	}

	int oldHitPoints = getEnergy();
	if (getStudentWorldPtr()->unitsOfFoodAt(getX(), getY()) > 0) {
		pickupAndEatFood(200);
	}

	if (oldHitPoints == getEnergy() || randInt(1, 2) == 1) {
		if (getDistanceToWalk() == 0) {
			setDirection(getRandomDir());
			setDistanceToWalkTo(randInt(2, 10));
		}
		if (moveForwardIfPossible())
			setDistanceToWalkTo(getDistanceToWalk() - 1);
		else
			setDistanceToWalkTo(0);
	}
	changeTicksBy(2);
}

bool BabyGrasshopper::canBeStunned()
{
	return true;
}

bool BabyGrasshopper::isEnemy(int colony) const
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////ADULT GRASSHOPPER IMPLEMENTATION////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

AdultGrasshopper::AdultGrasshopper(StudentWorld* sw, int x, int y)
	: Grasshopper(sw, IID_ADULT_GRASSHOPPER, x, y, 1600)
{}

void AdultGrasshopper::doSomething()
{
	updateEnergy(-1);
	if (isDead()) {
		setVisible(false);
		return;
	}
	else if (isSleeping()) {
		changeTicksBy(-1);
		return;
	}

	bool didBite = false;
	if (randInt(1, 3) == 1) {
		// if there is an enemy on the same square
		int numOfEnemies = getStudentWorldPtr()->numberOfEnemies(getX(), getY(), 4, this);
		if (numOfEnemies > 0) {
			// randomly bite enemy if on same square
			getStudentWorldPtr()->biteRandomEnemy(getX(), getY(), 4, randInt(1, numOfEnemies), this, getBite());
			didBite = true;
		}
	}

	bool didJump = false;
	if (!didBite) {
		if (randInt(1, 10) == 1) {
			// attempt to jump
			double theta = (randInt(1, 360) / 180.0) * 3.14159265;
			int length = randInt(0, 9);
			int tempX = length * cos(theta);
			int tempY = length * sin(theta);
			if (getX() + tempX < 0 || getX() + tempX >= VIEW_WIDTH ||
				getY() + tempY < 0 || getY() + tempY >= VIEW_WIDTH) {
				randInt(0, 9);
			}
			else if (!getStudentWorldPtr()->isPebbleAtDestination(tempX + getX(), tempY + getY())) {
				moveTo(tempX + getX(), tempY + getY());
				didJump = true;
			}
		}
	}

	if (!didJump) {
		// if did not move/jump
		int oldHitPoints = getEnergy();
		if (getStudentWorldPtr()->unitsOfFoodAt(getX(), getY()) > 0) {
			pickupAndEatFood(200);
		}

		if (oldHitPoints == getEnergy() || randInt(1, 2) == 1) {
			if (getDistanceToWalk() == 0) {
				setDirection(getRandomDir());
				setDistanceToWalkTo(randInt(2, 10));
			}
			if (moveForwardIfPossible())
				setDistanceToWalkTo(getDistanceToWalk() - 1);
			else
				setDistanceToWalkTo(0);
		}
	}
	changeTicksBy(2);
}

bool AdultGrasshopper::canBiteBack()
{
	return true;
}

int AdultGrasshopper::getBite()
{
	return 50;
}

bool AdultGrasshopper::canBeStunned()
{
	return false;
}