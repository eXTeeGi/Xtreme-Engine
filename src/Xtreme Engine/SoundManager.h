#ifndef _SoundManager
#define _SoundManager

#include <unordered_map>
#include "AzulCore.h"
#include "fmod_ALL.h"
using namespace std;

class SoundManager
{
	friend class SoundManagerAttorney;
public:
	static SoundManager* ptrinstance;

	static FMOD::Sound* Get2D(const string& argKey);
	static FMOD::Sound* Get3D(const string& argKey);

	static void Load2D(const string& argKey, const char* const argPath);
	static void Load3D(const string& argKey, const char* const argPath);

private:
	static SoundManager& Instance() {
		if (!ptrinstance)
			ptrinstance = new SoundManager;
		return *ptrinstance;
	}

	SoundManager();
	~SoundManager() {};
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator= (const SoundManager&) = delete;

	static void Delete();
	void privDelete();
	FMOD::Sound* privGet2D(const string& argKey);
	FMOD::Sound* privGet3D(const string& argKey);
	void privLoad2D(const string& argKey, const char* const argPath);
	void privLoad3D(const string& argKey, const char* const argPath);

	unordered_map<string, FMOD::Sound*> SoundMap2D;
	unordered_map<string, FMOD::Sound*> SoundMap3D;

	
};

#endif _SoundManager