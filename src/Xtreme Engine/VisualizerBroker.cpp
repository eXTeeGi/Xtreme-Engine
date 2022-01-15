#include "VisualizerBroker.h"
#include "CommandBase.h"

void VisualizerBroker::addCommand(CommandBase* argCmd) {
	lstCommands.push_back(argCmd);
}

void VisualizerBroker::ExecuteCommands() {
	std::list<CommandBase*>::const_iterator it;
	for (it = lstCommands.begin(); it != lstCommands.end(); ++it) {
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_V)) {
			(*it)->execute();
		}

	}

	lstCommands.clear();
}