#include "SceneRegistrationBroker.h"
#include "CommandBase.h"

void SceneRegistrationBroker::addCommand(CommandBase* argCmd) {
	lstCommands.push_back(argCmd);
}

void SceneRegistrationBroker::ExecuteCommands() {
	std::list<CommandBase*>::const_iterator it;
	for (it = lstCommands.begin(); it != lstCommands.end(); ++it) {
		(*it)->execute();
	}

	lstCommands.clear();
}