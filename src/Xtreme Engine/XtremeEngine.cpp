#include "AzulCore.h"
#include "XtremeEngine.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "SoundManagerAttorney.h"
#include "CameraManager.h"
#include "../Demo/Frigate.h"
#include "../Demo/WorldPlane.h"
#include "TimeManager.h"
#include "..//Demo/SceneDemo.h"
#include "SceneManager.h"
#include "ModelManagerAttorney.h"
#include "ShaderManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "KeyboardEventManager.h"
#include "VisualizerAttorney.h"
#include "VisualizerDrawBSphereCommandFactory.h"
#include "VisualizerDrawAABBCommandFactory.h"
#include "VisualizerDrawOBBCommandFactory.h"
#include "ImageManagerAttorney.h"
#include "SceneManagerAttorney.h"
#include "SpriteFontManagerAttorney.h"
#include "ScreenLog.h"
#include "ScreenLogAttorney.h"
#include "TerrainObjectManagerAttorney.h"
#include "SoundPlayerAttorney.h"

XtremeEngine* XtremeEngine::ptrinstance;

//-----------------------------------------------------------------------------
// XtremeEngine::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void XtremeEngine::Initialize()
{
	// XtremeEngine Window Device setup
	this->setWindowName("Xtreme Engine");
	this->setWidthHeight(800, 600);
	this->SetClearColor(0.6f, 0.9f, 1.0f, 1.0f);

	// Use this area, for one time non-graphic creation

	this->XtremeInitialize();
}

//-----------------------------------------------------------------------------
// XtremeEngine::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void XtremeEngine::LoadContent()
{

	ShaderManager::Load("Sprite", "spriteRender");
	ModelManager::Load("Sprite", Model::PreMadeModels::UnitSquareXY);
	SpriteFontManager::Load("Sans18", "ComicSans18");


	LoadResources();

	SceneManagerAttorney::InitStartScene();

	/*gobj1 = new Frigate();
	gobj2 = new WorldPlane();*/
}

//-----------------------------------------------------------------------------
// XtremeEngine::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void XtremeEngine::Update()
{
	TimeManager::ProcessTime(Engine::GetTimeInSeconds());

	SceneManagerAttorney::Update();

	SoundPlayerAttorney::Loop::Update();
}

//-----------------------------------------------------------------------------
// XtremeEngine::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void XtremeEngine::Draw()
{
	SceneManagerAttorney::Draw();

	//VisualizerAttorney::Draw::VisualizeAll();

	//SceneManagerAttorney::Draw2D();

	ScreenLogAttorney::Render();
}



//-----------------------------------------------------------------------------
// XtremeEngine::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void XtremeEngine::UnLoadContent()
{
	// general clean up.
	

	// (also: we should call 'delete' on all these global pointers we created... )
	TimeManager::Delete();

	SceneManagerAttorney::Delete();

	this->XtremeEnd();

	// Again, we are missing the shaders, textures, etc...
	ImageManagerAttorney::Delete();
	ShaderManagerAttorney::Delete();
	TextureManagerAttorney::Delete();
	ModelManagerAttorney::Delete();
	SpriteFontManagerAttorney::Delete();
	ScreenLogAttorney::Delete();
	SoundManagerAttorney::Delete();
	TerrainObjectManagerAttorney::Delete();
	SoundPlayerAttorney::Terminate::Delete();

	//SceneManager::Delete();
	

	VisualizerAttorney::Delete::Terminate();
	VisualizerDrawBSphereCommandFactory::Terminate();
	VisualizerDrawAABBCommandFactory::Terminate();
	VisualizerDrawOBBCommandFactory::Terminate();

	
}

void XtremeEngine::privDelete() {
	delete ptrinstance;
	ptrinstance = nullptr;
}

void XtremeEngine::Delete() {
	Instance().privDelete();
}

void XtremeEngine::pubRun() {
	Instance().run();
}