#include "Frigate.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "..//Xtreme Engine///CollisionVolumeBSphere.h"
#include "..//Xtreme Engine///ScreenLog.h"
#include "..////Xtreme Engine///TerrainObject.h"


Frigate::Frigate() {

	//FMOD
	FMOD_RESULT result;
	system = NULL;

	result = FMOD::System_Create(&system);      // Create the main system object.
	if (result != FMOD_OK)
	{
		//printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		//printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}


	fvPos = new FMOD_VECTOR();
	fvPosS = new FMOD_VECTOR();
	fvVel = new FMOD_VECTOR();
	fvVelS = new FMOD_VECTOR();
	fvFor = new FMOD_VECTOR();
	fvUp = new FMOD_VECTOR();

	
	


	fvPos->x = ShipPos[x];
	fvPos->y = ShipPos[y];
	fvPos->z = ShipPos[z];
	fvVel->x = 0;
	fvVel->y = 0;
	fvVel->z = 0;
	fvFor->x = ShipRot.get(ROW_2).X();
	fvFor->y = ShipRot.get(ROW_2).Y();
	fvFor->z = ShipRot.get(ROW_2).Z();
	fvUp->x = ShipRot.get(ROW_1).X();
	fvUp->y = ShipRot.get(ROW_1).Y();
	fvUp->z = ShipRot.get(ROW_1).Z();

	

	system->set3DListenerAttributes(0, fvPos, fvVel, fvFor, fvUp);

	
	exInfo = new FMOD_CREATESOUNDEXINFO();
	
	exInfo->cbsize = sizeof(FMOD_CREATESOUNDEXINFO);

	system->createSound("C:/Users/jakei/Desktop/School/Junior/Spring/Engine II/Perforce/berthiaume2020spring_gam377/student/jbarne30/Master/Xtreme Engine/Assets/Sounds/boom.wav",FMOD_3D,exInfo,&testSound);


	fvPosS;
	fvPosS->x = 0;
	fvPosS->y = 0;
	fvPosS->z = -200;
	fvVelS;
	fvVelS->x = 0;
	fvVelS->y = 0;
	fvVelS->z = 0;
	testChannel->setMode(FMOD_3D);
	testChannel->set3DAttributes(fvPosS, fvVelS);

	/*system->setOutput(FMOD_OUTPUTTYPE_AUDIO3D);
	system->createDSPByType(FMOD_DSP_TYPE_OBJECTPAN, &testDsp);
	testDsp->setParameterData(FMOD_DSP_OBJECTPAN_3D_POSITION, fvPosS, sizeof(FMOD_DSP_PARAMETER_3DATTRIBUTES_MULTI));

	FMOD_DSP_PARAMETER_3DATTRIBUTES_MULTI* testStuff = new FMOD_DSP_PARAMETER_3DATTRIBUTES_MULTI();
	testStuff->absolute = 0;*/

	system->playSound(testSound,0,false,&testChannel);

	




	pixels = new GLbyte[16];
	for (unsigned char i = 0; i < 255; ++i) {
		//texture by array test
		
		
		pixels[0] = Texture::UChartoGLbyte(i);	// Red
		pixels[1] = Texture::UChartoGLbyte(255);	// Green
		pixels[2] = 0;								// Blue
		pixels[3] = Texture::UChartoGLbyte(255);								// Alpha
		pixels[4] = 0;								// Red
		pixels[5] = 0;								// Green
		pixels[6] = 0;								// Blue
		pixels[7] = Texture::UChartoGLbyte(0);								// Alpha
		pixels[8] = 0;								// Red
		pixels[9] = 0;								// Green
		pixels[10] = 0;								// Blue
		pixels[11] = Texture::UChartoGLbyte(0);								// Alpha
		pixels[12] = Texture::UChartoGLbyte(i);	// Red
		pixels[13] = Texture::UChartoGLbyte(0);	// Green
		pixels[14] = 0;								// Blue
		pixels[15] = Texture::UChartoGLbyte(255);								// Alpha
		pRTTlist.push_back(new Texture(pixels, 2, 2, GL_NEAREST));
		
		
	}
	
	TextureManager::Load("SpaceFrigate", pRTTlist[0]);
	pRTTlist[0]->getName();

	//DebugMsg::out((char *)std::to_string(sizeof(Texture)).c_str());
	//sizeof(Texture);

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObjLT = new GraphicsObject_TextureLight(ModelManager::Get("Frigate"), ShaderManager::Get("TextureLight"), TextureManager::Get("SpaceFrigate"), LightColor, LightPos);

	/*Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObjWF = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ColorConstant"), Blue);*/

	// Creating matrices for in-world placement
	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	ShipRot.set(IDENTITY);
	ShipPos.set(0, 20, 0);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);

	SetColliderModel(pGObjLT->getModel(), Collidable::VolumeType::AABB);
	UpdateCollisionData(pGObjLT->getWorld());

	GameObject::SubmitEntry();
	SetCollidableGroup<Frigate>();
	SubmitCollisionRegistration();

	
}

void Frigate::Alarm0() {
	//Drawable::SubmitDrawDeregistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, 0.5f);

}

void Frigate::Alarm1() {
	//Drawable::SubmitDrawRegistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 0.5f);

}

Frigate::~Frigate() {
	delete pGObjLT;
	//delete pGObjWF;
	//delete pRTT;
	delete pixels;

	for (int i = 1; i < 255; ++i) {
		delete pRTTlist[i];
	}

	delete fvPos ;
	delete fvPosS;
	delete fvVel ;
	delete fvVelS;
	delete fvFor ;
	delete fvUp ;
	delete exInfo;
}

void Frigate::Update() {
	 fvVel;
	fvVel->x = 0;
	fvVel->y = 0;
	fvVel->z = 0;

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL)) {
		// Ship translation movement (not using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
		{
			ShipPos[Z] -= ShipTransSpeed;
			fvVel->x = ShipRot.get(ROW_2).getNorm().X() * ShipTransSpeed;
			fvVel->y = ShipRot.get(ROW_2).getNorm().Y() * ShipTransSpeed;
			fvVel->z = ShipRot.get(ROW_2).getNorm().Z() * ShipTransSpeed;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
		{
			ShipPos[Z] += ShipTransSpeed;
			fvVel->x = ShipRot.get(ROW_2).getNorm().X() * ShipTransSpeed;
			fvVel->y = ShipRot.get(ROW_2).getNorm().Y() * ShipTransSpeed;
			fvVel->z = ShipRot.get(ROW_2).getNorm().Z() * ShipTransSpeed;
		}

		// Ship Rotation movement (not using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
		{
			
			ShipPos[X] -= ShipTransSpeed;

		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
		{
			ShipPos[X] += ShipTransSpeed;
			

		}
	}
	Vect normaldude = SceneManager::GetTerrain()->getNormal(ShipPos.X(), ShipPos.Z());

	ShipRot.set(ROT_ORIENT,normaldude,Vect(0,1,0));

	// Spaceship adjust matrix
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObjLT->SetWorld(world);



	this->UpdateCollisionData(world);

	// Frigate::Update

	//pixels[0] = Texture::UChartoGLbyte(rand() % 255);
	//delete pRTT;
	//pRTT = new Texture(pixels, 2, 2, GL_NEAREST);
	++frame;



	//pGObjLT->textureID = pRTTlist[frame]->getTextureID();

	if (frame >= 254) frame = 0;

	fvPosS;
	fvPosS->x = 0;
	fvPosS->y = 0;
	fvPosS->z = -20;
	fvVelS;
	fvVelS->x = 0;
	fvVelS->y = 0;
	fvVelS->z = 0;
	testChannel->setMode(FMOD_3D);
	testChannel->set3DAttributes(fvPosS, fvVelS);

	 fvPos;
	fvPos->x = ShipPos[x];
	fvPos->y = ShipPos[y];
	fvPos->z = ShipPos[z];
	 fvFor;
	fvFor->x = ShipRot.get(ROW_2).X();
	fvFor->y = ShipRot.get(ROW_2).Y();
	fvFor->z = ShipRot.get(ROW_2).Z();
	 fvUp;
	fvUp->x = ShipRot.get(ROW_1).X();
	fvUp->y = ShipRot.get(ROW_1).Y();
	fvUp->z = ShipRot.get(ROW_1).Z();
	system->set3DListenerAttributes(0,fvPos,fvVel,fvFor,fvUp);
	//testDsp->setParameterData(FMOD_DSP_OBJECTPAN_3D_POSITION, fvPosS, sizeof(FMOD_DSP_PARAMETER_3DATTRIBUTES_MULTI));

	system->update();

	
}

void Frigate::orient(Vect& ) {
	//ShipRot.set(ROT_ORIENT, , argUp);
}

void Frigate::Draw() {
	//an attempt was made
	pGObjLT->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_INT, pixels);
	pGObjLT->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrentCamera());

}

void Frigate::SceneEntry() {
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 0.5f);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_UP, KeyboardEventManager::KEY_PRESS);

}

void Frigate::KeyPressed(AZUL_KEY k)
{
	if (!Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT)) {
		switch (k)
		{
		case AZUL_KEY::KEY_ARROW_UP:
			BulletFactory::CreateBullet(ShipRot, ShipScale, ShipPos);
			system->playSound(testSound, 0, false, &testChannel);

			break;

		default:
			DebugMsg::out("ERROR: Key %i unprocessed\n", k);
		}
	}
}

void Frigate::Collision(WorldPlane*) {


};

CollisionVolumeBSphere& Frigate::getBSphere() {
	return (CollisionVolumeBSphere&)Collidable::GetBSphere();
}

void Frigate::CollisionTerrain() {
}