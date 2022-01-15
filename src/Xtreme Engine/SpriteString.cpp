#include "SpriteString.h"
#include "SpriteFont.h"
#include "XtremeSprite.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CameraManager.h"

int SpriteString::GetHeight() {
	return height;
}

int SpriteString::GetWidth() {
	return width;
}

void SpriteString::Render() {
	float x = 0.0f;
	float y = 0.0f;
	int num = 0;

	std::vector<SpriteFont::Glyph*>::iterator it;
	for (it = glyphs.begin(); it != glyphs.end(); it++) {
		(*it)->SetPosition(posx+x,posy+y);
		(*it)->Render(SceneManager::GetCurrentScene()->getCamMan()->GetCurrent2DCamera());
		
		x += (*it)->getWidth() + 5;
		//x += 30;
		num++;
	}

}

void SpriteString::Set(int x, int y) {
	posx = x;
	posy = y;
}

void SpriteString::Set(SpriteFont* sf, std::string s, int x, int y) {
	sfont = sf;
	
	glyphs.clear();

	std::string::iterator it;
	for (it = s.begin(); it != s.end(); it++) {
		SpriteFont::Glyph* tmp = sfont->GetGlyph(*it);
		glyphs.push_back(tmp);
	}

	this->Set(x, y);
}

SpriteString::SpriteString() {
	height = 0;
	posx = 0;
	posy = 0;
	width = 0;
	sfont = nullptr;
}
/*
SpriteString::SpriteString(const SpriteFont& arg) {
	int height = 0;
	int posx = 0;
	int posy = 0;
	int width = 0;
	SpriteFont* sfont = arg;
}*/

SpriteString::SpriteString(SpriteFont* sf, std::string s, int x, int y) {
	height = 20;
	width = 30;

	Set(sf, s, x, y);
}
