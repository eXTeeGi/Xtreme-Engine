#ifndef _SceneChangeNullCommand
#define _SceneChangeNullCommand

#include "AzulCore.h"
#include "CommandBase.h"
#include "SceneChangeCommandBase.h"

class SceneChangeNullCommand : public SceneChangeCommandBase
{
public:
	SceneChangeNullCommand() = default;

	virtual void execute();
};

#endif _SceneChangeNullCommand