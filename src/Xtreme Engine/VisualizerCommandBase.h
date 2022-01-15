#ifndef _VisualizerCommandBase
#define _VisualizerCommandBase

#include "AzulCore.h"
#include "CommandBase.h"

class VisualizerCommandBase : public CommandBase
{
public:
	VisualizerCommandBase() {};
	VisualizerCommandBase(const VisualizerCommandBase&) = delete;
	VisualizerCommandBase& operator= (const VisualizerCommandBase&) = delete;
	virtual ~VisualizerCommandBase() {};
};

#endif _VisualizerCommandBase