#ifndef _SoundManagerAttorney
#define _SoundManagerAttorney

#include "SoundManager.h"
using namespace std;

class SoundManagerAttorney
{
	friend class XtremeEngine;
private:
	static void Delete() { SoundManager::Delete(); }
};

#endif _SoundManagerAttorney