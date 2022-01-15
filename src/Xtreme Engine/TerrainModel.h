#ifndef _TerrainModel
#define _TerrainModel

#include "AzulCore.h"

class Collidable;

class TerrainModel
{
public:
	TerrainModel(const char* const argPath, float len, float maxheight, int RepeatU, int RepeatV);
	~TerrainModel();

	Model* getModel() { return pModel; };
	void visualizeAABBs();

	void identifyCell(float x, float z);
	Vect& getNormal(float x, float z);
	void identifyUnder(Vect& min, Vect& max);
	void testCollision(Vect& min, Vect& max,Collidable*);

	/*int VertexIndex(int i, int j);
	int PixelIndex(int i, int j);
	int TriIndex(int i, int j);*/

private:
	Model* pModel;
	Vect* normalArr;
	Vect* MinMaxArr;
	int N_TRI;
	int N_VERTS;
	float _LEN;
	int _HGTW;
	float _BOTTOMBOUND;
};

#endif _TerrainModel