#include "TerrainObjectManager.h"
#include "TerrainObject.h"

TerrainObjectManager* TerrainObjectManager::ptrinstance;

TerrainObjectManager::TerrainObjectManager() {

}

void TerrainObjectManager::Delete() {
	Instance().privDelete();
}

TerrainObject* TerrainObjectManager::Get(const string& argKey) {
	return Instance().privGet(argKey);
}

void TerrainObjectManager::Load(const string& argKey, const char* const heightMap, float len, float maxheight, const char* const texName, int RepeatU, int RepeatV) {
	Instance().privLoad(argKey, heightMap,len,maxheight,texName,RepeatU,RepeatV);
}

void TerrainObjectManager::privDelete() {
	unordered_map<string, TerrainObject*>::iterator i;
	for (i = TerrainObjectMap.begin(); i != TerrainObjectMap.end(); i++)
	{
		delete i->second;
	}

	delete ptrinstance;
	ptrinstance = nullptr;
}

TerrainObject* TerrainObjectManager::privGet(const string& argKey) {
	assert(TerrainObjectMap.find(argKey) != TerrainObjectMap.end() && (argKey + " TerrainObject not loaded.").c_str());
	return TerrainObjectMap.find(argKey)->second;
}

void TerrainObjectManager::privLoad(const string& argKey, const char* const heightMap, float len, float maxheight, const char* const texName, int RepeatU, int RepeatV) {
	assert(TerrainObjectMap.find(argKey) == TerrainObjectMap.end() && (argKey + " TerrainObject loaded more than once.").c_str());
	TerrainObjectMap[argKey] = new TerrainObject(heightMap,len, maxheight,texName, RepeatU,RepeatV);
}