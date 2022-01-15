#include "ShaderManager.h"

ShaderManager* ShaderManager::ptrinstance;

ShaderManager::ShaderManager() {
	
}

void ShaderManager::Delete() {
	Instance().privDelete();
}

ShaderObject* ShaderManager::Get(const string& argKey) {
	return Instance().privGet(argKey);
}

void ShaderManager::Load(const string& argKey, const char* const argPath) {
	Instance().privLoad(argKey, argPath);
}

void ShaderManager::privDelete() {
	unordered_map<string, ShaderObject*>::iterator i;
	for (i = shaderMap.begin(); i != shaderMap.end(); i++)
	{
		delete i->second;
	}

	delete ptrinstance;
	ptrinstance = nullptr;
}

ShaderObject* ShaderManager::privGet(const string& argKey) {
	assert(shaderMap.find(argKey) != shaderMap.end() && (argKey + " shader not loaded.").c_str());
	return shaderMap.find(argKey)->second;
}

void ShaderManager::privLoad(const string& argKey, const char* const argPath) {
	assert(shaderMap.find(argKey) == shaderMap.end() && (argKey + " shader loaded more than once.").c_str());
	shaderMap[argKey] = new ShaderObject(("Shaders/" + (string)argPath).c_str());
}