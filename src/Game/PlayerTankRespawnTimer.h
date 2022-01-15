#ifndef _PlayerTankRespawnTimer
#define _PlayerTankRespawnTimer

#include "AzulCore.h"
#include "..//Xtreme Engine/GameObject.h"


class PlayerTankRespawnTimer : public GameObject
{
public:
	PlayerTankRespawnTimer();
private:
	virtual void Alarm0();
};

#endif _PlayerTankRespawnTimer