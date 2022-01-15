#ifndef _TextureManagerAttorney
#define _TextureManagerAttorney

#include "TextureManager.h"
using namespace std;

class TextureManagerAttorney
{
	friend class XtremeEngine;
private:
	static void Delete() { TextureManager::Delete(); }
};

#endif _TextureManagerAttorney