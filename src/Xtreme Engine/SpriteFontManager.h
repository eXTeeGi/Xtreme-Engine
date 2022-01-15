#ifndef _SpriteFontManager
#define _SpriteFontManager

#include <unordered_map>
#include "AzulCore.h"
using namespace std;

class SpriteFont;

class SpriteFontManager
{
	friend class SpriteFontManagerAttorney;
public:
	static SpriteFontManager* ptrinstance;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a sprite font* using the given argument key. </summary>
	///
	/// <remarks>	Jakei, 3/15/2020. </remarks>
	///
	/// <param name="argKey">	The Argument key to get. </param>
	///
	/// <returns>	Null if it fails, else a pointer to a SpriteFont. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static SpriteFont* Get(const string& argKey);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Loads. </summary>
	///
	/// <remarks>	Jakei, 3/15/2020. </remarks>
	///
	/// <param name="key"> 	The key. </param>
	/// <param name="path">	Full pathname of the file. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void Load(const string& key, const string& path);

private:
	static SpriteFontManager& Instance() {
		if (!ptrinstance)
			ptrinstance = new SpriteFontManager;
		return *ptrinstance;
	}

	SpriteFontManager();
	~SpriteFontManager() {};
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager& operator= (const SpriteFontManager&) = delete;

	static void Delete();
	void privDelete();
	SpriteFont* privGet(const string& argKey);
	void privLoad(const string& key, const string& path);

	unordered_map<string, SpriteFont*> fontMap;
	string DefaultPath;
};

#endif _SpriteFontManager