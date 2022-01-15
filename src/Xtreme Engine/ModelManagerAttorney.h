#ifndef _ModelManagerAttorney
#define _ModelManagerAttorney

#include "ModelManager.h"
using namespace std;

class ModelManagerAttorney
{
	friend class XtremeEngine;
private:
	static void Delete() { ModelManager::Delete(); }
};

#endif _ModelManagerAttorney