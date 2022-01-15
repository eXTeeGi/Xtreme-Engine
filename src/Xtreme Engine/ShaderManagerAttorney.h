#ifndef _ShaderManagerAttorney
#define _ShaderManagerAttorney

#include "ShaderManager.h"
using namespace std;

class ShaderManagerAttorney
{
	friend class XtremeEngine;
private:
	static void Delete() { ShaderManager::Delete(); }
};

#endif _ShaderManagerAttorney