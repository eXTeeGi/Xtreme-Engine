#ifndef _TerrainObjectManager
#define _TerrainObjectManager

#include <unordered_map>
#include "AzulCore.h"
using namespace std;

class TerrainObject;

class TerrainObjectManager
{
	friend class TerrainObjectManagerAttorney;
public:
	static TerrainObjectManager* ptrinstance;

	static TerrainObject* Get(const string& argKey);
	static void Load(const string& argKey, const char* const heightMap, float len, float maxheight, const char* const texName, int RepeatU, int RepeatV);

private:
	static TerrainObjectManager& Instance() {
		if (!ptrinstance)
			ptrinstance = new TerrainObjectManager;
		return *ptrinstance;
	}

	TerrainObjectManager();
	~TerrainObjectManager() {};
	TerrainObjectManager(const TerrainObjectManager&) = delete;
	TerrainObjectManager& operator= (const TerrainObjectManager&) = delete;

	static void Delete();
	void privDelete();
	TerrainObject* privGet(const string& argKey);
	void privLoad(const string& argKey, const char* const heightMap, float len, float maxheight, const char* const texName, int RepeatU, int RepeatV);

	unordered_map<string, TerrainObject*> TerrainObjectMap;
};

#endif _TerrainObjectManager