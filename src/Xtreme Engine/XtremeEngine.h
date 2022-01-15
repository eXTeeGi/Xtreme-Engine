#ifndef GAME_H
#define GAME_H

#include "AzulCore.h"

class Scene;

class XtremeEngine: public Engine
{
public:
	static XtremeEngine* ptrinstance;

	
	static void Delete();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets the name of the window. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argTitle">	The name you want to give the window. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void SetWindowName(const char* argTitle) { Instance().setWindowName(argTitle); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets the dimensions of the window. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argWidth"> 	Width. </param>
	/// <param name="argHeight">	Height. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void SetWidthHeight(int argWidth, int argHeight) { Instance().setWidthHeight(argWidth, argHeight); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets the color of the background using RGBA. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argRed">  	The red value. </param>
	/// <param name="argGreen">	The green value. </param>
	/// <param name="argBlue"> 	The blue value. </param>
	/// <param name="argAlpha">	The alpha value. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void SetClear(float argRed, float argGreen, float argBlue, float argAlpha) { Instance().SetClearColor(argRed, argGreen, argBlue, argAlpha); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the width of the window. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <returns>	The width. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static int GetWidth() { return Instance().getWidth(); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the height of the window. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <returns>	The height. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static int GetHeight() { return Instance().getHeight(); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the game time. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <returns>	The time. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static float GetTime() { return Instance().GetTimeInSeconds(); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Run the engine. </summary>
	///
	/// <remarks>	Jakei, 3/15/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void pubRun();

private:	
	static XtremeEngine& Instance() {
		if (!ptrinstance)
			ptrinstance = new XtremeEngine;
		return *ptrinstance;
	}

	void privDelete();

	// constructor
	XtremeEngine()
	{};

	// legacy
	XtremeEngine( const char* windowName, const int Width,const int Height);

	// Methods Users need to overload
	virtual void Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();

	//User defined
	void LoadResources();
	void XtremeEnd();
	void XtremeInitialize();
};

#endif