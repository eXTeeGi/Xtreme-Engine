#include "ModelManager.h"

ModelManager* ModelManager::ptrinstance;

ModelManager::ModelManager() {

}

void ModelManager::Delete() {
	Instance().privDelete();
}

Model* ModelManager::Get(const string& argKey) {
	return Instance().privGet(argKey);
}

void ModelManager::Load(const string& argKey, const char* const argPath) {
	Instance().privLoad(argKey, argPath);
}

void ModelManager::Load(const string& argKey, const Model::PreMadeModels argPMM) {
	Instance().privLoad(argKey, argPMM);
}

void ModelManager::privDelete() {
	unordered_map<string, Model*>::iterator i;
	for (i = modelMap.begin(); i != modelMap.end(); i++)
	{
		delete i->second;
	}
	
	delete ptrinstance;
	ptrinstance = nullptr;
}

Model* ModelManager::privGet(const string& argKey) {
	assert(modelMap.find(argKey) != modelMap.end() && (argKey + " model not loaded.").c_str());
	return modelMap.find(argKey)->second;
}

void ModelManager::privLoad(const string& argKey, const char* const argPath) {
	assert(modelMap.find(argKey) == modelMap.end() && (argKey + " model loaded more than once.").c_str());
	modelMap[argKey] = new Model(("Models/" + (string)argPath).c_str());
}

void ModelManager::privLoad(const string& argKey, const Model::PreMadeModels argPMM) {
	assert(modelMap.find(argKey) == modelMap.end() && (argKey + " model loaded more than once.").c_str());
	modelMap[argKey] = new Model(argPMM);
}