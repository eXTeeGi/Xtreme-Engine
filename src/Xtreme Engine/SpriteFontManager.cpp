#include "SpriteFontManager.h"
#include "SpriteFont.h"

SpriteFontManager* SpriteFontManager::ptrinstance;

SpriteFontManager::SpriteFontManager() {
}

void SpriteFontManager::Delete() {
	Instance().privDelete();
}

SpriteFont* SpriteFontManager::Get(const string& argKey) {
	return Instance().privGet(argKey);
}

void SpriteFontManager::Load(const string& key, const string& path) {
	Instance().privLoad(key, path);
}


void SpriteFontManager::privDelete() {
	unordered_map<string, SpriteFont*>::iterator i;
	for (i = fontMap.begin(); i != fontMap.end(); i++)
	{
		delete i->second;
	}

	//delete r;

	delete ptrinstance;
	ptrinstance = nullptr;
}


SpriteFont* SpriteFontManager::privGet(const string& argKey) {
	assert(fontMap.find(argKey) != fontMap.end() && (argKey + " sprint font not loaded.").c_str());
	return fontMap.find(argKey)->second;
}

void SpriteFontManager::privLoad(const string& key, const string& path) {
	assert(fontMap.find(key) == fontMap.end() && (key + " font loaded more than once.").c_str());
	fontMap[key] = new SpriteFont(key.c_str(),path.c_str());
}
