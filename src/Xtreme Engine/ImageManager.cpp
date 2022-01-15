#include "ImageManager.h"

ImageManager* ImageManager::ptrinstance;

ImageManager::ImageManager() {
}

void ImageManager::Delete() {
	Instance().privDelete();
}

Image* ImageManager::Get(const string& argKey) {
	return Instance().privGet(argKey);
}

void ImageManager::Load(const string& argKey, Texture* argTex) {
	Instance().privLoad(argKey, argTex);
}

void ImageManager::Load(const string& argKey, Texture* argTex, Rect* argR) {
	Instance().privLoad(argKey, argTex, argR);
}

void ImageManager::privDelete() {
	unordered_map<string, Image*>::iterator i;
	for (i = imageMap.begin(); i != imageMap.end(); i++)
	{
		delete i->second;
	}

	//delete r;

	delete ptrinstance;
	ptrinstance = nullptr;
}


Image* ImageManager::privGet(const string& argKey) {
	assert(imageMap.find(argKey) != imageMap.end() && (argKey + " image not loaded.").c_str());
	return imageMap.find(argKey)->second;
}

void ImageManager::privLoad(const string& argKey, Texture* argTex) {
	assert(imageMap.find(argKey) == imageMap.end() && (argKey + " image loaded more than once.").c_str());
	Rect* tmpR = new Rect(0.0f, 0.0f, (float)argTex->getWidth(), (float)argTex->getHeight());
	imageMap[argKey] = new Image(argTex, tmpR);
}

void ImageManager::privLoad(const string& argKey, Texture* argTex, Rect* argR) {
	assert(imageMap.find(argKey) == imageMap.end() && (argKey + " image loaded more than once.").c_str());
	imageMap[argKey] = new Image(argTex, argR);
}

ImageManager::~ImageManager() {}