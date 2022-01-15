#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker

#include "AzulCore.h"
#include <list>
class CommandBase;

class SceneRegistrationBroker
{
public:
	void addCommand(CommandBase* c);
	void ExecuteCommands();
private:
	using StorageList = std::list<CommandBase*>;
	StorageList lstCommands;
};

#endif _SceneRegistrationBroker