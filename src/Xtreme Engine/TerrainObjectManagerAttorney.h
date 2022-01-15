#ifndef _TerrainObjectManagerAttorney
#define _TerrainObjectManagerAttorney

#include "TerrainObjectManager.h"
using namespace std;

class TerrainObjectManagerAttorney
{
	friend class XtremeEngine;
private:
	static void Delete() { TerrainObjectManager::Delete(); }
};

#endif _TerrainObjectManagerAttorney