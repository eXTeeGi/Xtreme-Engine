#ifndef _SoundPlayer
#define _SoundPlayer

#include "AzulCore.h"
#include "fmod_ALL.h"
#include <list>
#include <string>
using namespace std;

class Collidable;

class SoundPlayer
{
	friend class SoundPlayerAttorney;
public:
	static SoundPlayer* ptrinstance;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Plays a 2D sound of the given name. </summary>
	///
	/// <param name="key">	The name of the sound. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void playSound(const string& key) { Instance().privPlaySound(key); };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Plays a 3D sound of the given name at the given coordinates. </summary>
	///
	/// <param name="key">	The name of the sound. </param>
	/// <param name="pos">	The position of the sound. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void playSound(const string& key, Vect& pos) { Instance().privPlaySound(key, pos); };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets the position of the listener (usually the player position). Should be updated whenever it moves. </summary>
	///
	/// <param name="pos">	The position of the listener. </param>
	/// <param name="forward">	The forward vector of the listener. </param>
	/// <param name="up">	The up vector of the listener. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void setListenerPos(Vect pos, Vect forward, Vect up) { Instance().privListener(pos, forward, up); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Register a collidable for the ability to block sounds! </summary>
	///
	/// <param name="c">	The collidable. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void registerForOcclusion(Collidable* c) { Instance().privRegister(c); };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	DEregister a collidable FROM the ability to block sounds. </summary>
	///
	/// <param name="c">	The collidable. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void deregisterForOcclusion(Collidable* c) { Instance().privDeregister(c); };
private:
	SoundPlayer();

	static SoundPlayer& Instance() {
		if (!ptrinstance)
			ptrinstance = new SoundPlayer;
		return *ptrinstance;
	}
	static void Terminate();
	void privTerminate();
	
	void privPlaySound(const string& argKey);
	void privPlaySound(const string& argKey, Vect& argPos);

	void privListener(Vect pos, Vect forward, Vect up);

	void privRegister(Collidable*);
	void privDeregister(Collidable*);

	//Management
	static FMOD::System* getSystem() { return Instance().system; }
	static FMOD_CREATESOUNDEXINFO* getExInfo() { return Instance().exInfo; }

	//Loop
	static void Update() { Instance().privUpdate(); };
	void privUpdate();

	int listenerID;
	int maxIDs = 600;

	std::list<Collidable*> occludables;
	Vect listenerPosV;

	//FMOD
	FMOD::System* system;
	FMOD_CREATESOUNDEXINFO* exInfo;
	FMOD::Channel* Channel2D;
	FMOD::Channel* Channel3D;
	std::list<FMOD::Channel*> channels;
	FMOD::DSP* testDsp;
	FMOD_VECTOR* soundPos;
	FMOD_VECTOR* soundVel;
	FMOD_VECTOR* listenerPos;
	FMOD_VECTOR* listenerVel;
	FMOD_VECTOR* listenerFor;
	FMOD_VECTOR* listenerUp;
};

#endif _SoundPlayer