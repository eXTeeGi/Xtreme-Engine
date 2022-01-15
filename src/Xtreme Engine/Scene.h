#ifndef _Scene
#define _Scene

#include "AzulCore.h"
#include "UpdatableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "KeyboardEventManager.h"
#include "CollisionManager.h"
#include "CollisionManager.h"
#include <list>

class SceneRegistrationBroker;
class CommandBase;
class Inputable;
class CameraManager;
class Collidable;
class TerrainObject;

class Scene
{
	friend class SceneAttorney;
public:
	Scene();
	virtual ~Scene();
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Use this to set up the scene. (Creating initial objects, etc.)  </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Initialize() = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is called when the scene ends. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void SceneEnd() = 0;

	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the camera manager. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <returns>	Null if it fails, else the camera manager. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	CameraManager* getCamMan() {return cameraMan;};

	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the collision manager. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <returns>	Null if it fails, else the collision manager. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	CollisionManager* GetCollisionManager();

	TerrainObject* GetTerrain() { return terrainObj; }
protected:

	void SetTerrain(const char* const terrainKey);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Tells the system to look for collisions between the given object types. </summary>
	///
	/// <typeparam name="C1">	First object type. </typeparam>
	/// <typeparam name="C2">	Second object type. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template< typename C1, typename C2>
	void SetCollisionPair()
	{
		ColMgr->SetCollisionPair<C1, C2>();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Tells the system to look for collisions between an object and another of the same type. </summary>
	///
	/// <typeparam name="C">	Object type. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template< typename C>
	void SetCollisionSelf()
	{
		ColMgr->SetCollisionSelf<C>();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Tells the system to look for collisions between an object and the terrain. </summary>
	///
	/// <typeparam name="C">	Object type. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template< typename C>
	void SetCollisionTerrain()
	{
		ColMgr->SetCollisionTerrain<C>();
	}

private:
	
	void Update();
	void Draw();
	//void Draw2D();

	//Updatable
	void Register(Updatable*, UpdatableManager::StorageListRef&);
	void Deregister(UpdatableManager::StorageListRef);

	//Drawable
	void Register(Drawable*, DrawableManager::StorageListRef&);
	void Deregister(DrawableManager::StorageListRef);

	//Alarmable
	void Register(float, Alarmable*, AlarmableManager::ALARM_ID, AlarmableManager::StorageMapRef&);
	void Deregister(AlarmableManager::StorageMapRef&);

	//Inputable
	void Register(Inputable*, AZUL_KEY, KeyboardEventManager::EVENT_TYPE);
	void Deregister(Inputable*, AZUL_KEY, KeyboardEventManager::EVENT_TYPE);

	void SubmitCommand(CommandBase* argCmd);

	void CreateGodCam();

	void runBroker();

	UpdatableManager* UpdateMgr;
	DrawableManager* DrawMgr;
	AlarmableManager* AlarmMgr;
	KeyboardEventManager* KBEventMgr;
	CameraManager* cameraMan;
	CollisionManager* ColMgr;
	SceneRegistrationBroker* RegistrationBrkr;
	TerrainObject* terrainObj;
};

#endif _Scene