#ifndef _SpriteFont
#define _SpriteFont

#include "AzulCore.h"
#include <map>
#include <string>
#include <xmllite.h>

class XtremeSprite;

class SpriteFont
{
public:
	using Key = int;
	using Glyph = XtremeSprite;
public:
	Texture* FontTexture;
private:
	std::string Name;
	
	using FontMap = std::map< Key, Glyph* >;
	FontMap fontmap;
	Rect* r = nullptr;

	// Parse the XML file
	void XMLtoCollection(std::string filename);

	// Tool: Reads & converts an XML attribute into an int
	void ElementTextToInt(IXmlReader* pReader, int& out);


public:
	SpriteFont(const char* name, const char* path);
	Glyph* GetGlyph(char c);

	~SpriteFont();
	SpriteFont() = default;
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;
};

#endif _SpriteFont