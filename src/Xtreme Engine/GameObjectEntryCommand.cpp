#include "GameObjectEntryCommand.h"
#include "GameObject.h"

GameObjectEntryCommand::GameObjectEntryCommand(GameObject* argGO)
	: ptrGO(argGO)
{

}

void GameObjectEntryCommand::execute() {
	ptrGO->ConnectToScene();
}