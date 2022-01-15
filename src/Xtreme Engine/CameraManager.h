#ifndef _CameraManager
#define _CameraManager

#include <unordered_map>
#include "AzulCore.h"

using namespace std;

class GodCam;

class CameraManager
{
public:
	CameraManager();
	~CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator= (const CameraManager&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the current 3D camera for 3D rendering. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <returns>	Null if it fails, else the current camera. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Camera* GetCurrentCamera();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets the current 3D camera. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argNewCam">	[in,out] If non-null, the argument new camera. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SetCurrentCamera(Camera* argNewCam);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the 2D camera for sprite rendering. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <returns>	Null if it fails, else the current 2D camera. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Camera* GetCurrent2DCamera();

	void SwitchToGod();
	void SwitchFromGod();
	void createGod();

private:
	
	Matrix* godRot;

	Camera* TwoD;

	Camera* camCurrent;
	Camera* DefaultCamera;
	Camera* god;
	Camera* notGod;

	GodCam* godObj;
};

#endif _CameraManager