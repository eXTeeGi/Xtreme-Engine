#ifndef _GameObjectExitCommand
#define _GameObjectExitCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
class GameObject;

class GameObjectExitCommand : public SceneRegistrationCommand
{
public:
	GameObjectExitCommand(GameObject*);

	virtual void execute();

	GameObject* ptrGO;
};

#endif _GameObjectExitCommand