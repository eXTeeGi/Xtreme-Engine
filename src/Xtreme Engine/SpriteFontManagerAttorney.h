#ifndef _SpriteFontManagerAttorney
#define _SpriteFontManagerAttorney

#include "SpriteFontManager.h"
using namespace std;

class SpriteFontManagerAttorney
{
	friend class XtremeEngine;
private:
	static void Delete() { SpriteFontManager::Delete(); }
};

#endif _SpriteFontManagerAttorney