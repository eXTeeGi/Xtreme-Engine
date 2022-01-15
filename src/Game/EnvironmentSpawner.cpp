#include "EnvironmentSpawner.h"
#include "PlayerTankManager.h"
#include "Die.h"
#include "Rock.h"

EnvironmentSpawner::EnvironmentSpawner() {

}

EnvironmentSpawner::~EnvironmentSpawner() {
	while (!dieList.empty()) {
		delete dieList.front();
		dieList.pop_front();
	}

	while (!rockList.empty()) {
		delete rockList.front();
		rockList.pop_front();
	}
}

void EnvironmentSpawner::generate() {
	//dice
	Vect ptPos = PlayerTankManager::getPlayerTankPos();
	int numDice = 50;
	Matrix rotM = Matrix(ROT_Y, (MATH_PI * 2) / numDice) /** Matrix(TRANS, ptPos)*/;
	Vect spawnHere = ((ptPos + Vect(0.0f, 0.0f, 1.0f)) - ptPos).getNorm();
	for (int i = 0; i < numDice; ++i) {
		rotM = Matrix(ROT_Y, (float)(rand() % 628) / 100);
		dieList.push_back(new Die(Vect(0, 50.0f, 0) + ((spawnHere * rotM) * (((float)(rand() % 2500)) + 500))));
	}

	//rock
	int numRocks = 50;
	rotM = Matrix(ROT_Y, (MATH_PI * 2) / numDice) /** Matrix(TRANS, ptPos)*/;
	for (int i = 0; i < numRocks; ++i) {
		rotM = Matrix(ROT_Y, (float)(rand() % 628) / 100);
		rockList.push_back(new Rock(Vect(0, 0, 0) + ((spawnHere * rotM) * (((float)(rand() % 2000)) + 500))));
	}
}

void EnvironmentSpawner::generateBoss() {
	//dice
	Vect ptPos = PlayerTankManager::getPlayerTankPos();
	int numDice = 50;
	Matrix rotM = Matrix(ROT_Y, (MATH_PI * 2) / numDice) /** Matrix(TRANS, ptPos)*/;
	Vect spawnHere = ((ptPos + Vect(0.0f, 0.0f, 1.0f)) - ptPos).getNorm();
	for (int i = 0; i < numDice; ++i) {
		rotM = Matrix(ROT_Y, (float)(rand() % 628) / 100);
		dieList.push_back(new Die(Vect(0, 50.0f, 0) + ((spawnHere * rotM) * (((float)(rand() % 2500)) + 500))));
	}
}

void EnvironmentSpawner::generateTutorial() {
	//dice
	Vect ptPos = PlayerTankManager::getPlayerTankPos();
	int numDice = 20;
	Matrix rotM = Matrix(ROT_Y, (MATH_PI * 2) / numDice) /** Matrix(TRANS, ptPos)*/;
	Vect spawnHere = ((ptPos + Vect(0.0f, 0.0f, 1.0f)) - ptPos).getNorm();
	for (int i = 0; i < numDice; ++i) {
		rotM = Matrix(ROT_Y, (float)(rand() % 628) / 100);
		dieList.push_back(new Die(Vect(0, 50.0f, 0) + ((spawnHere * rotM) * (((float)(rand() % 2500)) + 500))));
	}
}