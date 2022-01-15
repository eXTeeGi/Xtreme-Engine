
#ifndef _FreezeTime
#define _FreezeTime

#include "AzulCore.h"

class FreezeTime
{
	friend class FreezeTimeAttorney;
private:
	static const AZUL_KEY FREEZE_KEY = AZUL_KEY::KEY_F10;
	static const AZUL_KEY SINGLE_FRAME_KEY = AZUL_KEY::KEY_F9;

	float totalFrozenTime;
	bool freeze_mode_active;

	float WaitAndReturnFrozenTime(float activetime);
	bool HackedKeyRelease(AZUL_KEY k);

	FreezeTime();
	~FreezeTime() {};
	FreezeTime(const FreezeTime&) = delete;
	FreezeTime& operator=(const FreezeTime&) = delete;

	float GetTimeInSeconds(float sys_time);

public:
	
};

#endif _FreezeTime