#ifndef _SceneChangeCommand
#define _SceneChangeCommand

#include "AzulCore.h"
#include "CommandBase.h"
#include "SceneChangeCommandBase.h"

class Scene;

class SceneChangeCommand : public SceneChangeCommandBase
{
public:
	SceneChangeCommand(Scene*);

	virtual void execute();

private:
	Scene* ptr;
};

#endif _SceneChangeCommand