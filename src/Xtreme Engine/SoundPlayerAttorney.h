#ifndef _SoundPlayerAttorney
#define _SoundPlayerAttorney

#include "SoundPlayer.h"

class SoundPlayerAttorney
{
public:
	class Management {
		friend class SoundManager;
	public:
		static FMOD::System* getSystem() { return SoundPlayer::getSystem(); }
		static FMOD_CREATESOUNDEXINFO* getExInfo() { return SoundPlayer::getExInfo(); }
	};

	class Loop {
		friend class XtremeEngine;
	public:
		static void Update() { SoundPlayer::Update(); }
	};

	class Terminate {
		friend class XtremeEngine;
	public:
		static void Delete() { SoundPlayer::Terminate(); }
	};
};


#endif _SoundPlayerAttorney