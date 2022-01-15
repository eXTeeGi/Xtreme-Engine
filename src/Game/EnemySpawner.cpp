#include "EnemySpawner.h"

#include "EnemyTank.h"
#include "EnemyTankFactory.h"
#include "RushTankFactory.h"
#include "TrainingTargetFactory.h"
#include "PlayerTankManager.h"
#include "UFOFactory.h"

EnemySpawner* EnemySpawner::ptrinstance;

EnemySpawner::EnemySpawner() {
}

void EnemySpawner::Update() {

}

void EnemySpawner::Draw() {

}

void EnemySpawner::Alarm0() {
	/*EnemyTank* pet = new EnemyTank(Vect(0,0,0));
	pet->Initialize(Vect((float)(rand() % 1000), 0, (float)(rand() % 1000)));*/
	EnemyTankFactory::CreateEnemyTank(Vect((float)(rand() % 1000), 0, (float)(rand() % 1000)));

	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 2.0f);
}

void EnemySpawner::privStartRandomSpawning() {
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 2.0f);

}

void EnemySpawner::privStopRandomSpawning() {
	Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);

}

void EnemySpawner::privSpawnTanksInCircle(int argNum,float argRadius) {
	//Vect ptPos = PlayerTankManager::getPlayerTankPos();
	Vect ptPos = Vect(0, 0, 0);

	Matrix rotM =  Matrix(ROT_Y, (MATH_PI * 2) / argNum) /** Matrix(TRANS, ptPos)*/;
	Vect spawnHere = ((ptPos + Vect(0.0f,0.0f, 1.0f)) - ptPos).getNorm();
	EnemyTankFactory::CreateEnemyTank(ptPos + (spawnHere * argRadius));
	int i;
	for (i = 1; i < argNum; i++) {
		//vertices[i] = vertices[i - 1] * rotM;
		spawnHere = spawnHere * rotM;
		EnemyTankFactory::CreateEnemyTank(ptPos + (spawnHere * argRadius));
	}
}

void EnemySpawner::privSpawnRushTanksInCircle(int argNum,float argRadius) {
	//Vect ptPos = PlayerTankManager::getPlayerTankPos();
	Vect ptPos = Vect(0,0,0);

	Matrix rotM = Matrix(ROT_Y, (MATH_PI * 2) / argNum) /** Matrix(TRANS, ptPos)*/;
	Vect spawnHere = ((ptPos + Vect(0.0f, 0.0f, 1.0f)) - ptPos).getNorm();
	RushTankFactory::CreateRushTank(ptPos + (spawnHere * argRadius));
	int i;
	for (i = 1; i < argNum; i++) {
		//vertices[i] = vertices[i - 1] * rotM;
		spawnHere = spawnHere * rotM;
		RushTankFactory::CreateRushTank(ptPos + (spawnHere * argRadius));
	}
}

void EnemySpawner::privSpawnTargetsInCircle(int argNum, float argRadius) {
	//Vect ptPos = PlayerTankManager::getPlayerTankPos();
	Vect ptPos = Vect(0, 0, 0);

	Matrix rotM = Matrix(ROT_Y, (MATH_PI * 2) / argNum) /** Matrix(TRANS, ptPos)*/;
	Vect spawnHere = ((ptPos + Vect(0.0f, 0.0f, 1.0f)) - ptPos).getNorm();
	TrainingTargetFactory::CreateTarget(Vect(0, 15.0f, 0) + (ptPos + (spawnHere * argRadius)));
	int i;
	for (i = 1; i < argNum; i++) {
		//vertices[i] = vertices[i - 1] * rotM;
		spawnHere = spawnHere * rotM;
		TrainingTargetFactory::CreateTarget(Vect(0, 15.0f, 0) + (ptPos + (spawnHere * argRadius)));
	}
}

void EnemySpawner::privSpawnUFOsInCircle(int argNum, float argRadius) {
	//Vect ptPos = PlayerTankManager::getPlayerTankPos();
	Vect ptPos = Vect(0, 0, 0);
	float altitude = 300.0f;

	Matrix rotM = Matrix(ROT_Y, (MATH_PI * 2) / argNum) /** Matrix(TRANS, ptPos)*/;
	Vect spawnHere = ((ptPos + Vect(0.0f, 0.0f, 1.0f)) - ptPos).getNorm();
	UFOFactory::CreateUFO(Vect(0, altitude, 0) + (ptPos + (spawnHere * argRadius)));
	int i;
	for (i = 1; i < argNum; i++) {
		//vertices[i] = vertices[i - 1] * rotM;
		spawnHere = spawnHere * rotM;
		altitude += 30.0f;
		UFOFactory::CreateUFO(Vect(0, altitude, 0) + (ptPos + (spawnHere * argRadius)));
	}
}

void EnemySpawner::Delete() {
	//Instance().privDelete();

	delete ptrinstance;
	ptrinstance = nullptr;
}

void EnemySpawner::privDelete() {
	
}