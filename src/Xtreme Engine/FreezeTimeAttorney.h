#ifndef _FreezeTimeAttorney
#define _FreezeTimeAttorney

#include "FreezeTime.h"

class FreezeTimeAttorney
{
public:
	friend class TimeManager;

	static FreezeTime* newFreezeTime() { return new FreezeTime(); };
	static void deleteFreezeTime(FreezeTime* p) { delete p; };
	static float gTIS(FreezeTime* p, float sys_time) { return p->GetTimeInSeconds(sys_time); };
};


#endif _FreezeTimeAttorney