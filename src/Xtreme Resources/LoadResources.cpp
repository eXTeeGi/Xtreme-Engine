#include "../Xtreme Engine/XtremeEngine.h"
#include "../Xtreme Engine/ShaderManager.h"
#include "../Xtreme Engine/TextureManager.h"
#include "../Xtreme Engine/ModelManager.h"
#include "..//Xtreme Engine/SceneManager.h"
#include "..//Xtreme Engine/SoundManager.h"
#include "..//Demo/SceneDemo.h"
#include "..//Game/SceneGameTest.h"
#include "..//Xtreme Engine/ImageManager.h"
#include "..//Xtreme Engine/SpriteFontManager.h"
#include "..//Game/PlayerTankManager.h"
#include "..//Xtreme Engine/TerrainObjectManager.h"
#include "../Game/SceneTutorial.h"

void XtremeEngine::LoadResources() {
	//---------------------------------------------------------------------------------------------------------
	// Load the Models
	//---------------------------------------------------------------------------------------------------------

	ModelManager::Load("Frigate", "space_frigate.azul");
	ModelManager::Load("Bullet", "bullet_case.azul");
	//ModelManager::Load("Frigate", "space_frigate.azul"); //for testing duplicate keys
	ModelManager::Load("Axis", "Axis.azul");
	ModelManager::Load("Plane", "Plane.azul");
	ModelManager::Load("Tank", "Tank.azul");
	ModelManager::Load("Turret", "Turret.azul");
	ModelManager::Load("Fence", "Fence.azul");
	ModelManager::Load("Cottage", "Cottage.azul");
	ModelManager::Load("Panther", "Panther.azul");
	ModelManager::Load("t99tank", "t99body.azul");
	ModelManager::Load("t99turret", "t99turret.azul");
	ModelManager::Load("Rock", "Rock1.azul");
	ModelManager::Load("UFO", "UFO.azul");
	ModelManager::Load("Sphere", Model::PreMadeModels::UnitSphere);
	ModelManager::Load("Box", Model::PreMadeModels::UnitBox_WF);

	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------

	TextureManager::Load("Frigate", "space_frigate.tga");
	TextureManager::Load("GridTex", "grid.tga");
	TextureManager::Load("BulletTex", "bullet_tex.tga");
	TextureManager::Load("Stitch", "stitch.tga");

	

	//TextureManager::Load("Stitch", pixels,2,2);
	//TextureManager::Load("SpaceFrigate", pixels, 2, 2);

	TextureManager::Load("Heart", "heart.tga");
	TextureManager::Load("WoodFloor", "wood_floor.tga");
	TextureManager::Load("Grass", "Grass.tga");
	TextureManager::Load("TankGreen", "GoodTank.tga");
	TextureManager::Load("TankTan", "BadTank.tga");
	TextureManager::Load("Cottage", "Cabintexture.tga");
	TextureManager::Load("CubeTest", "CubeTest.tga");
	TextureManager::Load("Target", "target.tga");
	TextureManager::Load("Stone", "Stone.tga");
	TextureManager::Load("HMT", "HMTest16.tga");
	TextureManager::Load("AmmoCrate", "ammocrate.tga");
	TextureManager::Load("SpeedBoost", "speedboost.tga");
	TextureManager::Load("ufo", "ufo.tga");
	TextureManager::Load("Crosshair", "Crosshair.tga");

	//---------------------------------------------------------------------------------------------------------
	// Load the Shaders
	//---------------------------------------------------------------------------------------------------------

	ShaderManager::Load("TextureFlat", "textureFlatRender");
	ShaderManager::Load("TextureLight", "textureLightRender");
	ShaderManager::Load("ColorConstant", "colorConstantRender");
	ShaderManager::Load("ColorNoTexture", "colorNoTextureRender");

	ImageManager::Load("Stitch", TextureManager::Get("Stitch"));
	ImageManager::Load("Heart", TextureManager::Get("Heart"));
	ImageManager::Load("Crosshair",TextureManager::Get("Crosshair"));

	SpriteFontManager::Load("Sans30", "ComicSans30");
	SpriteFontManager::Load("Sans16", "ComicSans16");

	SoundManager::Load2D("Boom", "boom.wav");
	SoundManager::Load2D("BAM", "boom.wav");
	SoundManager::Load3D("Boom", "boom.wav");
	SoundManager::Load3D("BAM", "boom.wav");
	SoundManager::Load2D("Cave", "cave.wav");
	SoundManager::Load2D("Reload", "reload.wav");
	SoundManager::Load2D("Boost", "boost.wav");
	SoundManager::Load3D("Sonar", "sonar.wav");
	SoundManager::Load3D("Explosion", "explosion.mp3");
	SoundManager::Load3D("Pop", "pop.wav");

	TerrainObjectManager::Load("Test","Textures/heightmap.tga", 1000, 50,"Grass" ,1, 1);

	SceneManager::SetStartScene(new SceneTutorial());
	
}