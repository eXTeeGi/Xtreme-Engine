
/** \defgroup API XtremeEngine API
\brief These commands are available to XtremeEngine users
*/

/** \defgroup GAMEOBJECT GameObject
\ingroup API
\brief All game entities will be derived from GameObject.
*/

/** \defgroup INPUTABLE Input events.
\ingroup GAMEOBJECT
\brief Callbacks can be triggered on GameObjects for input events you set up.

These input events must be registered first.

Example:
	\code
	Frigate::Frigate() {
		//Set up key event
		SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEventManager::KEY_PRESS);
	}

	//Call back is triggered when any registered key event is triggered
	void Frigate::KeyPressed(AZUL_KEY k) {
		switch (k)
		{
		case AZUL_KEY::KEY_SPACE:
			// Fire bullet or something here, idk
			break;
		default:
			DebugMsg::out("ERROR: Key %i unprocessed\n", k);
		}
	}
	\endcode
*/

/** \defgroup ALARMABLE Alarms
\ingroup GAMEOBJECT

\brief Callbacks can be triggered by an alarm.

Alarms begin when they are registered.

Example:
	\code
	Frigate::Frigate() {
		//Registration
		SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0,10.0f);
	}

	//Call back is triggered when the corresponding alarm runs out of time.
	void Frigate::Alarm0() {
		//idk why you would want to set an alarm for your Frigate on construction, but you can!
	}
	\endcode
*/

/** \defgroup COLLIDABLE Collisions
\ingroup GAMEOBJECT
\brief 
*/

/** \defgroup UPDATABLE Update step
\ingroup GAMEOBJECT
\brief
*/

/** \defgroup DRAWABLE Draw step
\ingroup GAMEOBJECT
\brief
*/

/** \defgroup RESOURCES Resources
\ingroup API
\brief Loading external resources into the game.
*/

/** \defgroup SCENE Scene
\ingroup API
\brief 
*/


/** \defgroup INTERNAL Internal to XtremeEngine
\brief Browse the Xtremely elegant internal workings of XtremeEngine.
*/

/** \defgroup TOOLS Helpful Tools
\brief Debug tools.
*/

/** \defgroup GODCAM God Camera
\ingroup TOOLS
\brief During runtime, you can hold shift to change to the God Camera.

As long as you are holding shift, you can move the camera using WASD and the arrow keys.

Use this to get a better look at your scene.

Releasing Left Shift will change the camera back to whatever it was before.

You may want to program anything you programmed with WASD and arrow keys to be disabled while holding shift.
*/

/** \defgroup VISUALIZER Collision Volume Visualizer
\ingroup TOOLS
\brief During runtime, you can hold V to show the B-spheres of every object being tested for collision.

You may want to program anything you programmed to use the V key to use a different key.
*/

/** \defgroup SCREENLOG On-Screen Debug Messages
\ingroup TOOLS
\brief By using ScreenLog::Add(), you can create debug messages that will be printed on the bottom left of the screen in size 18 Comic Sans MS font.

\par Example:
	\code
	ScreenLog::Add("Pos: %3.1f, %3.1f, %3.1f", ShipPos[x], ShipPos[y], ShipPos[z]);
	\endcode

The formatting is similar to that of printf().

The messages will be rendered once and deleted at the end of the frame, so if you want it to stay on screen, you will need to add it every frame.
For example: The example above is in the Frigate's update method, so a new message is created each frame with the updated Frigate position.
*/

/**************************************************************************************************************/


/*! \mainpage About XtremeEngine

XtremeEngine is a 3D game engine.

\section features Features
With XtremeEngine you can:
	- Create 3D Game Objects
	- Create 2D Sprites
	- Set Alarms
	- Process Collisions
	- and SO MUCH MORE!!!

Requires competent C++ skills.

*/

/*! \page START Getting Started
\subpage GS_FIRST Setting up your first scene.

*/

/*! \page GS_FIRST First Scene
	This page will walk you through making a simple project using XtremeEngine.

	\par Setting up a scene:
	You will need to create an object that derives from Scene. This object represents a world space, or level, for your game.
		\code
		#ifndef _ExampleScene
		#define _ExampleScene

		#include "../Xtreme Engine/Scene.h"

		class ExampleScene : public Scene
		{
		public:
			SceneGameTest() = default;
			~SceneGameTest();

			virtual void Initialize();
			virtual void SceneEnd();

		private:
			//pointers to objects you want the scene to create, so you can manage them later
		};

		#endif _ExampleScene
		\endcode
	Once a scene is created, you will need to set it as the starting scene in LoadResources.cpp, like so:
		\code
		void XtremeEngine::LoadResources() {
			SceneManager::SetStartScene(new ExampleScene());
		}
		\endcode
\par First Object:
	You will need to create an object that derives from GameObject.
		\code
		#ifndef _Frigate
		#define _Frigate

		#include "AzulCore.h"
		#include "../Xtreme Engine/GameObject.h"

		class Frigate : public GameObject
		{
		public:
			Frigate();
			~Frigate();

			virtual void Update() override;
			virtual void Draw() override;

		private:
			GraphicsObject_TextureLight* pGObjLT;
			Vect ShipPos;
			Matrix ShipRot;
			Matrix ShipScale;
			const float ShipTransSpeed = 1;
			const float ShipRotAng = .05f;
		};

		#endif _Frigate
		\endcode
	In the constructor, you will need to create the graphics object for the ship, register it for update and draw, and position it in the world.
		\code
		Frigate::Frigate() {
			//Graphics Object
			Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
			Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
			pGObjLT = new GraphicsObject_TextureLight(ModelManager::Get("Frigate"), ShaderManager::Get("TextureLight"), TextureManager::Get("SpaceFrigate"), LightColor, LightPos);

			//Position
			Matrix world;
			ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
			ShipRot.set(IDENTITY);
			ShipPos.set(0, 20, 0);
			world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
			pGObjLT->SetWorld(world);

			//Registration
			SubmitUpdateRegistration();
			SubmitDrawRegistration();
		}
		\endcode
	The Model, Shader, and Texture will need to be loaded in LoadResources.cpp
		\code
		ModelManager::Load("Frigate", "space_frigate.azul");
		ShaderManager::Load("TextureLight", "textureLightRender");
		TextureManager::Load("SpaceFrigate", "space_frigate.tga");
		\endcode
	In the draw method for the Frigate, you will want to call Render on the graphics object, so you can see the Frigate.
		\code
		void Frigate::Draw() {
			pGObjLT->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
		}
		\endcode
	In the update method, add some controls!
		\code
		void Frigate::Update() {
			if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT)) { //<---This is to avoid moving the ship while the god cam is active.
				
				if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
				{
					ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
				}
				else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
				{
					ShipPos += Vect(0, 0, 1) * ShipRot * -ShipTransSpeed;
				}

				if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
				{
					ShipRot *= Matrix(ROT_Y, ShipRotAng);
				}
				else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
				{
					ShipRot *= Matrix(ROT_Y, -ShipRotAng);
				}
			}

			// Spaceship adjust matrix
			Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
			pGObjLT->SetWorld(world);
		}
		\endcode
	Before you can test out your ship, you will need to place one in the scene.
	Add a Frigate* to SceneDemo and create a new Frigate in the scene Initializer.
	Then, delete it in SceneEnd();
		\code
		void SceneDemo::Initialize() {
			GOFrig = new Frigate();
		}


		void SceneDemo::SceneEnd() {
			delete GOFrig;
		}
		\endcode
	Now you should be able to launch the game and move the Frigate around with WASD.
*/


