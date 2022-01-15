#ifndef _SceneManager
#define _SceneManager

#include "AzulCore.h"

class Scene;
class SceneChangeNullCommand;
class SceneChangeCommand;
class SceneChangeCommandBase;
class TerrainObject;

class SceneManager
{
	friend class SceneManagerAttorney;
public:
	static SceneManager* ptrinstance;

	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a pointer to the current scene. </summary>
	///
	/// <remarks>	Jakei, 3/3/2020. </remarks>
	///
	/// <returns>	Null if it fails, else the current scene. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Scene* GetCurrentScene() { return Instance().privGetCurrentScene(); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets the first scene of the game. Call this in LoadResources. </summary>
	///
	/// <remarks>	Jakei, 3/3/2020. </remarks>
	///
	/// <param name="argScene">	The scene pointer. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void SetStartScene(Scene* argScene) { Instance().privSetStartScene(argScene); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Call this to change the scene. </summary>
	///
	/// <remarks>	Jakei, 3/3/2020. </remarks>
	///
	/// <param name="arg">	The scene pointer. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void SetNextScene(Scene* arg) { Instance().privSetNextScene(arg); };
	
	static TerrainObject* GetTerrain() { return Instance().privGetTerrain(); }

private:
	static SceneManager& Instance() {
		if (!ptrinstance)
			ptrinstance = new SceneManager;
		return *ptrinstance;
	}

	SceneManager();
	~SceneManager() {};
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	Scene* ptrCurrentScene;

	SceneChangeCommandBase* ptrSceneChangeCmd;
	SceneChangeNullCommand* ChangeNullCmd;

	static void Delete() { Instance().privDelete(); }
	static void InitStartScene() { Instance().privInitStartScene(); }
	static void ChangeScene(Scene* arg) { Instance().privChangeScene(arg); }
	static void Draw() { Instance().privDraw(); }
	//static void Draw2D() { Instance().privDraw2D(); }
	static void Update() { Instance().privUpdate(); }

	void privDelete();
	void privDraw();
	//void privDraw2D();
	Scene* privGetCurrentScene();
	void privInitStartScene();
	void privSetStartScene(Scene* argScene);
	void privUpdate();
	void privSetNextScene(Scene*);
	void privChangeScene(Scene*);
	TerrainObject* privGetTerrain();
};

#endif _SceneManager