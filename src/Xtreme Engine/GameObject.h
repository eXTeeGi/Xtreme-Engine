#ifndef _GameObject
#define _GameObject

#include "AzulCore.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collidable.h"
#include "../Xtreme Engine/ModelManager.h"
#include "../Xtreme Engine/ShaderManager.h"
#include "../Xtreme Engine/TextureManager.h"
#include "../Xtreme Engine/CameraManager.h"

class GameObjectExitCommand;
class GameObjectEntryCommand;

class GameObject: public Updatable, public Drawable, public Alarmable, public Inputable, public Collidable
{
	
public:
	GameObject();
	virtual  ~GameObject();
	 GameObject(const GameObject&) = delete;
	 GameObject& operator=(const GameObject&) = delete;

	void ConnectToScene();
	void DisconnectFromScene();

	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit entry into the scene. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitEntry();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit exit from the scene. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitExit();
protected:
	enum class RegistrationState
	{
		CURRENTLY_DEREGISTERED,
		PENDING_REGISTRATION,
		CURRENTLY_REGISTERED,
		PENDING_DEREGISTRATION
	};
	RegistrationState getRegState();
private:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is called when the object is registered to the scene. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void SceneEntry() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is called when the object exits the scene. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void SceneExit() {};

	RegistrationState currState;
	GameObjectExitCommand* pDeregCmd;
	GameObjectEntryCommand* pRegCmd;
};

#endif _GameObject