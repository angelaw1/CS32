#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "Compiler.h"



// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
	Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, int depth);
	// virtual ~Actor();
	virtual void doSomething() = 0;
	virtual bool isDead() const;
	virtual bool blocksInsects() const;
	virtual void getBitten(int amt);
	virtual void getPoisoned();
	virtual void getStunned();
	Direction getRandomDir();
	StudentWorld* getStudentWorldPtr();
	bool hasMoved();
	void setMoveStatus(bool statement);
	virtual bool canBeEaten() const;
	virtual bool canBeBitten();
	virtual bool alreadyStunned();
	virtual void setStunnedTo(bool statement);
	virtual bool canBeStunned();
	bool canBePoisoned();
	virtual int getBite();
	virtual bool canBiteBack();
	virtual bool isPheromone(int colony) const;
	virtual bool isEnemy(int colony) const;
	virtual bool isDangerous(int colony) const;
	virtual bool isAntHill(int colony) const;
private:
	StudentWorld* m_studentWorldPtr;
	bool m_isAlive;
	bool m_hasMoved;
};

class EnergyHolder : public Actor {
public:
	EnergyHolder(StudentWorld* sw, int startX, int startY, Direction startDir, int energy, int imageID, int depth);
	virtual void doSomething() = 0;
	virtual bool isDead() const;
	int getEnergy();
	void updateEnergy(int amt);
	void addFood(int amt);
	int pickupFood(int amt);
	int pickupAndEatFood(int amt);
	virtual bool becomesFoodUponDeath() const;
	void setDead();
	int getFood();
	void updateFood(int amt);
private:
	int m_energy;
	int m_food;
};

class Insect : public EnergyHolder {
public:
	Insect(StudentWorld* sw, int imageID, int x, int y, int energy);
	virtual void doSomething() = 0;
	virtual void changeTicksBy(int diff);
	bool isSleeping();
	virtual bool canBeBitten();
	virtual bool alreadyStunned();
	virtual void setStunnedTo(bool statement);
	virtual void getBitten(int amt);
	virtual void getPoisoned();
	virtual void getStunned();
	virtual bool isEnemy(int colony);
	virtual bool becomesFoodUponDeath() const;
	void getXYInFrontOfMe(int &x, int &y) const;
	virtual bool moveForwardIfPossible();
	virtual bool canBeStunned();
private:
	int m_hitPoints;
	int m_ticksLeft;
	bool m_alreadyStunned;
};

class TriggerableActor : public Actor
{
public:
	TriggerableActor(StudentWorld* sw, int x, int y, int imageID);
	virtual void doSomething() = 0;
	virtual bool isDangerous(int colony) const;
};


class Ant : public Insect {
public:
	Ant(StudentWorld* sw, int startX, int startY, int colony, Compiler* program, int imageID);
    virtual void doSomething();
    virtual void getBitten(int amt);
    virtual bool isEnemy(int colony) const;
	bool simpleInterpreter(Compiler* c);
	virtual bool isDangerous(int colony);
private:
	int m_colonyNum;
	int m_instructionCounter;
	Compiler* m_antCompiler;
	int m_lastRandNum;
	bool m_bitten;
	vector<string> m_blocked;
	vector<string> m_notBlocked;
	int m_oldX;
	int m_oldY;
};


class Pebble : public Actor {
public:
	Pebble(StudentWorld* sw, int x, int y);
	virtual void doSomething();
	virtual bool blocksInsects() const;
};

class Food : public EnergyHolder {
public:
	Food(StudentWorld* sw, int x, int y, int units);
	virtual void doSomething();
	virtual bool canBeEaten() const;
private:
	int m_units;
};

class Pheromone : public EnergyHolder {
public:
	Pheromone(StudentWorld* sw, int x, int y, int colony);
	virtual void doSomething();
	virtual bool isPheromone(int colony) const;
private:
	int m_colony;
};

class Anthill : public EnergyHolder {
public:
	Anthill(StudentWorld* sw, int x, int y, int colonyNum, Compiler* program);
	virtual ~Anthill();
	virtual void doSomething();
	virtual bool canBeBitten();
	virtual bool isAntHill(int colony) const;
private:
	int m_colonyNum;
	Compiler* m_program;
};

class Water : public TriggerableActor {
public:
	Water(StudentWorld* sw, int x, int y);
	virtual void doSomething();
};

class Poison : public TriggerableActor{
public:
	Poison(StudentWorld* sw, int x, int y);
	virtual void doSomething();
};

class Grasshopper : public Insect {
public :
	Grasshopper(StudentWorld* sw, int imageID, int x, int y, int energy);
	virtual void doSomething() = 0;
	void setDistanceToWalkTo(int distance);
	int getDistanceToWalk();
	virtual bool isDangerous(int colony);
private:
	int m_distanceToWalk;
};

class BabyGrasshopper : public Grasshopper {
public:
	BabyGrasshopper(StudentWorld* sw, int x, int y);
	virtual bool isEnemy(int colony) const;
	virtual void doSomething();
	virtual bool canBeStunned();
};

class AdultGrasshopper : public Grasshopper {
public:
	AdultGrasshopper(StudentWorld* sw, int x, int y);
	virtual void doSomething();
	virtual bool canBiteBack();
	virtual int getBite();
	virtual bool canBeStunned();
};

#endif // ACTOR_H_