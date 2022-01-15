#include "SceneChangeCommand.h"
#include "SceneManager.h"
#include "SceneManagerAttorney.h"

SceneChangeCommand::SceneChangeCommand(Scene* arg) {
	ptr = arg;
}

void SceneChangeCommand::execute() {
	SceneManagerAttorney::ChangeScene(ptr);
}