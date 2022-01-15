#ifndef _SceneChangeCommandBase
#define _SceneChangeCommandBase

#include "AzulCore.h"
#include "CommandBase.h"

class Scene;

class SceneChangeCommandBase : public CommandBase
{
public:
	virtual ~SceneChangeCommandBase() {};
private:
	Scene* ptr;
};

#endif _SceneChangeCommandBase