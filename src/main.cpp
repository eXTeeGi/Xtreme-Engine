
#include "Xtreme Engine/XtremeEngine.h"

int CALLBACK WinMain(HINSTANCE , HINSTANCE ,  LPSTR , int)                  
{          
	// create XtremeEngine
	//XtremeEngine *pGame = new XtremeEngine();    

	// start the game 
	XtremeEngine::pubRun();

	// "clean-up"... (not really for these demos)
	XtremeEngine::Delete();

	return 0;                                       
}

