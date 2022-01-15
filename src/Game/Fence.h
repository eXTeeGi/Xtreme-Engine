#ifndef _Fence
#define _Fence

#include "AzulCore.h"
#include "../Xtreme Engine/GameObject.h"
#include <list>

class Fence: public GameObject
{
public:
	Fence();
	~Fence();

	virtual void Draw();


private:
	void generateFence(int width);

	GraphicsObject_TextureLight* pGO;
	std::list< GraphicsObject_TextureLight*> pGOList;
};

#endif _Fence