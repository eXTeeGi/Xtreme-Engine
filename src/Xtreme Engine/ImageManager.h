#ifndef _ImageManager
#define _ImageManager

#include <unordered_map>
#include "AzulCore.h"
using namespace std;

class ImageManager
{
	friend class ImageManagerAttorney;
public:
	static ImageManager* ptrinstance;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the image of the given name/key. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey">	The name/key of the image. </param>
	///
	/// <returns>	Null if it fails, else a pointer to an Image. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static Image* Get(const string& argKey);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Stores an image using a given texture. Rect is automatic. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey">	The name/key you want to give to the image. </param>
	/// <param name="tex">   	The texture. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void Load(const string& argKey, Texture* tex);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Stores an image using a given texture and rect. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey">	The name/key you want to give to the image. </param>
	/// <param name="tex">   	The texture. </param>
	/// <param name="r">	 	The Rect. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void Load(const string& argKey, Texture* tex, Rect* r);

private:
	static ImageManager& Instance() {
		if (!ptrinstance)
			ptrinstance = new ImageManager;
		return *ptrinstance;
	}

	ImageManager();
	~ImageManager();
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator= (const ImageManager&) = delete;

	static void Delete();
	void privDelete();
	Image* privGet(const string& argKey);
	void privLoad(const string& argKey, Texture* tex);
	void privLoad(const string& argKey, Texture* tex, Rect* r);

	unordered_map<string, Image*> imageMap;
	string DefaultPath;
};

#endif _ImageManager