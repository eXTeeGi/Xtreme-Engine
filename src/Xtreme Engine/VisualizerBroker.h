#ifndef _VisualizerBroker
#define _VisualizerBroker

#include "AzulCore.h"
#include <list>
class CommandBase;

class VisualizerBroker
{
public:
	void addCommand(CommandBase* c);
	void ExecuteCommands();

	VisualizerBroker() {};
	~VisualizerBroker() {};
	VisualizerBroker(const VisualizerBroker&) = delete;
	VisualizerBroker& operator=(const VisualizerBroker&) = delete;
private:
	using StorageList = std::list<CommandBase*>;
	StorageList lstCommands;
};

#endif _VisualizerBroker