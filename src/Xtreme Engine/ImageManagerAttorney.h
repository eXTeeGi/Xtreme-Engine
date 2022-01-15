#ifndef _ImageManagerAttorney
#define _ImageManagerAttorney

#include "ImageManager.h"
using namespace std;

class ImageManagerAttorney
{
	friend class XtremeEngine;
private:
	static void Delete() { ImageManager::Delete(); }
};

#endif _ImageManagerAttorney