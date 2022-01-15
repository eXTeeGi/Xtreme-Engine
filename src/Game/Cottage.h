#ifndef _Cottage
#define _Cottage

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
#include <list>
#include "..//Xtreme Engine/SceneManager.h"

class Cottage : public GameObject
{
public:
	Cottage();
	 ~Cottage();

	virtual void Draw();


private:

	GraphicsObject_TextureLight* pGO;
};

#endif _Cottage