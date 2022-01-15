#include "TextureManager.h"

TextureManager* TextureManager::ptrinstance;

void TextureManager::Delete() {
	Instance().privDelete();
}

Texture* TextureManager::Get(const string& argKey) {
	return Instance().privGet(argKey);
}

void TextureManager::Load(const string& argKey, const char* const argPath) {
	Instance().privLoad(argKey, argPath);
}

void TextureManager::Load(const string& argKey, const unsigned char& argRed, const unsigned char& argGreen, const unsigned char& argBlue, const unsigned char& argAlpha) {
	Instance().privLoad(argKey, argRed, argBlue, argGreen, argAlpha);
}

void TextureManager::Load(const string& argKey, GLbyte* pixArray, int width, int height, int filtermode) {
	Instance().privLoad( argKey, pixArray,  width,  height,  filtermode);
}

void TextureManager::Load(const string& argKey, Texture* argTex) {
	Instance().privLoad(argKey, argTex);
}

void TextureManager::privDelete() {
	unordered_map<string, Texture*>::iterator i;
	for (i = textureMap.begin(); i != textureMap.end(); i++)
	{
		delete i->second;
	}

	delete ptrinstance;
	ptrinstance = nullptr;
}

Texture* TextureManager::privGet(const string& argKey) {
	assert(textureMap.find(argKey) != textureMap.end() && (argKey + " texture not loaded.").c_str());
	return textureMap.find(argKey)->second;
}

void TextureManager::privLoad(const string& argKey, const char* const argPath) {
	assert(textureMap.find(argKey) == textureMap.end() && (argKey + " texture loaded more than once.").c_str());
	textureMap[argKey] = new Texture(("Textures/" + (string)argPath).c_str());
}

void TextureManager::privLoad(const string& argKey, const unsigned char& argRed, const unsigned char& argGreen, const unsigned char& argBlue, const unsigned char& argAlpha) {
	assert(textureMap.find(argKey) == textureMap.end() && (argKey + " texture loaded more than once.").c_str());
	textureMap[argKey] = new Texture(argRed,argBlue,argGreen,argAlpha);
}

void TextureManager::privLoad(const string& argKey, GLbyte* pixArray, int width, int height, int filtermode) {
	assert(textureMap.find(argKey) == textureMap.end() && (argKey + " texture loaded more than once.").c_str());
	textureMap[argKey] = new Texture( pixArray,  width,  height,  filtermode);
}

void TextureManager::privLoad(const string& argKey, Texture* argTex) {
	assert(textureMap.find(argKey) == textureMap.end() && (argKey + " texture loaded more than once.").c_str());
	textureMap[argKey] = argTex;
}