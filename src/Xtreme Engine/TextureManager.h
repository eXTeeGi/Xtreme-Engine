#ifndef _TextureManager
#define _TextureManager

#include <unordered_map>
#include "AzulCore.h"
using namespace std;

class TextureManager
{
	friend class TextureManagerAttorney;
public:
	static TextureManager* ptrinstance;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a texture* using the given key. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey">	The name/key of the texture to get. </param>
	///
	/// <returns>	Null if it fails, else a pointer to a Texture. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Texture* Get(const string& argKey);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Loads and stores a texture from the given file path. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey"> 	The key/name you want to give the texture. </param>
	/// <param name="argPath">	Full pathname of the texture file. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void Load(const string& argKey, const char * const argPath);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Stores a solid color texture from given RGBA values. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey">  	The name/key you want to give the texture. </param>
	/// <param name="argRed">  	The red value. </param>
	/// <param name="argGreen">	The green value. </param>
	/// <param name="argBlue"> 	The blue value. </param>
	/// <param name="argAlpha">	The alpha value. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void Load(const string& argKey, const unsigned char& argRed, const unsigned char& argGreen, const unsigned char& argBlue, const unsigned char& argAlpha);

	static void Load(const string& argKey, GLbyte* pixArray, int width, int height, int filtermode = GL_NEAREST);

	static void Load(const string& argKey, Texture* argTex);

private:
	static TextureManager& Instance() {
		if (!ptrinstance)
			ptrinstance = new TextureManager;
		return *ptrinstance;
	}

	TextureManager() {};
	~TextureManager() {};
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator= (const TextureManager&) = delete;

	static void Delete();
	void privDelete();
	Texture* privGet(const string& argKey);
	void privLoad(const string& argKey, const char* const argPath);
	void privLoad(const string& argKey, const unsigned char& argRed, const unsigned char& argGreen, const unsigned char& argBlue, const unsigned char& argAlpha);
	void privLoad(const string& argKey, GLbyte* pixArray, int width, int height, int filtermode);
	void privLoad(const string& argKey, Texture* argTex);

	unordered_map<string, Texture*> textureMap;
};

#endif _TextureManager