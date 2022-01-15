#ifndef _GameObjectEntryCommand
#define _GameObjectEntryCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
class GameObject;

class GameObjectEntryCommand : public SceneRegistrationCommand
{
public:
	GameObjectEntryCommand(GameObject*);

	virtual void execute();

	GameObject* ptrGO;
};

#endif _GameObjectEntryCommand