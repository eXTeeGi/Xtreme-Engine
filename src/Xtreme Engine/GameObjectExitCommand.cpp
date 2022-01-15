#include "GameObjectExitCommand.h"
#include "GameObject.h"

GameObjectExitCommand::GameObjectExitCommand(GameObject* argGO)
	: ptrGO(argGO)
{

}

void GameObjectExitCommand::execute() {
	ptrGO->DisconnectFromScene();
}