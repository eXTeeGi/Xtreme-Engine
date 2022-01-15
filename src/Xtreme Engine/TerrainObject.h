#ifndef _TerrainObject
#define _TerrainObject

#include "AzulCore.h"

class CameraManager;
class Collidable;

class TerrainObject
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Create a terrain. </summary>
	///
	/// <param name="argPath">	A heightmap tga file that will determine the terrain shape. </param>
	/// <param name="len">	The desired length of the terrain. </param>
	/// <param name="maxheight">	The heighest point on the terrain. </param>
	/// <param name="texName">	The name of the texture to be applied to the terrain. </param>
	/// <param name="RepeatU">	The amount of texture repeats in the u direction. </param>
	/// <param name="RepeatV">	The amount of texture repeats in the v direction. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	TerrainObject(const char* const argPath, float len, float maxheight, const char* const texName, int RepeatU, int RepeatV);
	~TerrainObject();

	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the model from the Terrain. </summary>
	///
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Model* getModel() { return pModel; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Visualizes the AABBs of the terrain. </summary>
	///
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void visualizeAABBs();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Identify the cell at any x and z position within the boudaries of the terrain. </summary>
	///
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void identifyCell(float x, float z);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the normal at any x and z position of the terrain. </summary>
	///
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Vect getNormal(float x, float z);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Visualizes all AABBs on the terrain below a given AABB. </summary>
	///
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void identifyUnder(Vect& min, Vect& max);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Performs an intersect test with terrain and given collidable. </summary>
	///
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void Intersect(Collidable*);


	void Draw(CameraManager*);
private:
	void testCollision(Vect& min, Vect& max, Collidable*);

	Model* pModel;
	Vect* normalArr;
	Vect* MinMaxArr;
	VertexStride_VUN* pVerts;
	TriangleIndex* pTriList;
	int N_TRI;
	int N_VERTS;
	float _LEN;
	int _HGTW;
	float _BOTTOMBOUND;
	GraphicsObject_TextureLight* pGO;
	GraphicsObject_WireframeConstantColor* pWF;
};

#endif _TerrainObject