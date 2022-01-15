#ifndef _Visualizer
#define _Visualizer

#include "AzulCore.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolume;
class VisualizerBroker;

class Visualizer: public Align16
{
	friend class VisualizerAttorney;
private:
	static Visualizer* ptrinstance;

	Visualizer();
	~Visualizer() {};
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;

	static Visualizer& Instance() {
		if (!ptrinstance)
			ptrinstance = new Visualizer;
		return *ptrinstance;
	}
	
	void privDelete();

	//static Vect DEFAULT_COLOR;
	GraphicsObject_WireframeConstantColor* WFUnitSphere;
	GraphicsObject_WireframeConstantColor* WFUnitBox;
	VisualizerBroker* vBrok;

	void privShowCollisionVolume(const CollisionVolume& S, const Vect& col/* = DEFAULT_COLOR*/);

	void privShowBSphere(const CollisionVolumeBSphere& S, const Vect& col/* = DEFAULT_COLOR*/);
	void privShowBSphere(Vect& center, const Vect& col/* = DEFAULT_COLOR*/);
	void privShowAABB(const CollisionVolumeAABB& S, const Vect& col/* = DEFAULT_COLOR*/);
	void privShowAABB(Vect& min, Vect& max, const Vect& col/* = DEFAULT_COLOR*/);
	void privShowOBB(const CollisionVolumeOBB& S, const Vect& col/* = DEFAULT_COLOR*/);

	void privRenderBSphere(Matrix& S, const Vect& col);
	void privRenderAABB(Matrix& S, const Vect& col);
	void privRenderOBB(Matrix& S, const Vect& col);

	void VisualizeAll();

	static void Delete();

public:
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Visualizes a collision volume. </summary>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void ShowCollisionVolume(const CollisionVolume& S, const Vect& col/* = DEFAULT_COLOR*/);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Visualizes a bsphere. </summary>
	///
	/// <param name="S">	The bsphere. </param>
	/// <param name="col">	The desired color of bsphere. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col/* = DEFAULT_COLOR*/);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Visualizes a bsphere. </summary>
	///
	/// <param name="center">	The center of the bsphere. </param>
	/// <param name="col">	The desired color of bsphere. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void ShowBSphere(Vect& center, const Vect& col/* = DEFAULT_COLOR*/);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Visualizes an AABB. </summary>
	///
	/// <param name="S">	The AABB. </param>
	/// <param name="col">	The desired color of AABB. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void ShowAABB(const CollisionVolumeAABB& S, const Vect& col/* = DEFAULT_COLOR*/);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Visualizes an AABB. </summary>
	///
	/// <param name="min">	The min corner of the AABB. </param>
	/// <param name="max">	The max corner of the AABB. </param>
	/// <param name="col">	The desired color of AABB. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void ShowAABB(Vect& min, Vect& max, const Vect& col/* = DEFAULT_COLOR*/);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Visualizes an OBB. </summary>
	///
	/// <param name="S">	The  OBB. </param>
	/// <param name="col">	The desired color of OBB. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void ShowOBB(const CollisionVolumeOBB& S, const Vect& col/* = DEFAULT_COLOR*/);
};

#endif _Visualizer