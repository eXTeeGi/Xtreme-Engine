#ifndef _CommandBase
#define _CommandBase

#include "AzulCore.h"

class CommandBase
{
public:
	virtual void execute() = 0;
};

#endif _CommandBase