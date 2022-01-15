#include "PlayerTankRespawnTimer.h"

#include "PlayerTankManager.h"

PlayerTankRespawnTimer::PlayerTankRespawnTimer() {
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 2.0f);
}

void PlayerTankRespawnTimer::Alarm0() {
	PlayerTankManager::respawnPlayer();
}