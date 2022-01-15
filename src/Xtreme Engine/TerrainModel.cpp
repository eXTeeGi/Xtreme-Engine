#include "TerrainModel.h"
#include "TextureTGA.h"
#include "GpuVertTypes.h"
#include "ShaderManager.h"
#include "Visualizer.h"
#include "XtremeColors.h"
#include "CollisionVolumeAABB.h"
#include "XtremeMath.h"
#include "Collidable.h"
#include "ScreenLog.h"

TerrainModel::TerrainModel(const char* const argPath, float len, float maxheight, int RepeatU, int RepeatV) {
	int imgWidth, imgHeigth, icomp;
	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits(argPath, &imgWidth, &imgHeigth, &icomp, &dtype);
	assert(imgWidth == imgHeigth && imgWidth != 0);
	
	// ** much work to add below **
	int heightMapW = imgWidth;
	int nverts = heightMapW * heightMapW;
	VertexStride_VUN* pVerts = new VertexStride_VUN[nverts];
	int ntri = 2 * ((heightMapW - 1) * (heightMapW - 1));
	TriangleIndex* pTriList = new TriangleIndex[ntri];

	//bound
	float bottomBound = -len / 2;

	//Vertices
	int vind = 0;
	int x = 0, y = 0;
	for (int i = 0; i < heightMapW; i++) {
		for (int j = 0; j < heightMapW; j++) {
			float xF = bottomBound + (x * (len / heightMapW));
			float yF = bottomBound + (y * (len / heightMapW));
			//float h = ((float)hgtmap->pixels[TexelIndex(hgtmap->height, x, y)] / 255) * maxheight;
			float h = ((float)(static_cast<unsigned char>(imgData[(j + (i * imgWidth)) * 3])) / 255) * maxheight;
			//float u = (float)x / (heightMapW - 1);
			float u = (((float)x / (heightMapW - 1)) * RepeatU);
			//float v = (float)y / (heightMapW - 1);
			float v = ((float)y / (heightMapW - 1)) * RepeatV;
			pVerts[vind].set(xF, h, yF, u, v,0,0,0);
			vind++;
			x++;
		}

		x = 0;
		y++;
	}

	normalArr = new Vect[nverts];
	//Normals
	for (int n = 0; n < nverts; n++) {
		if (n % heightMapW != 0 && n % heightMapW != heightMapW - 1 && n >= heightMapW && n < heightMapW * (heightMapW - 1)) {
			Vect v1 = pVerts[n - heightMapW].getV() - pVerts[n].getV();
			Vect v2 = pVerts[n - heightMapW + 1].getV() - pVerts[n].getV();
			Vect v3 = pVerts[n + 1].getV() - pVerts[n].getV();
			Vect v4 = pVerts[n + heightMapW].getV() - pVerts[n].getV();
			Vect v5 = pVerts[n + heightMapW - 1].getV() - pVerts[n].getV();
			Vect v6 = pVerts[n - 1].getV() - pVerts[n].getV();
			Vect f1 = v2.cross(v1).getNorm();
			Vect f2 = v3.cross(v2).getNorm();
			Vect f3 = v4.cross(v3).getNorm();
			Vect f4 = v5.cross(v4).getNorm();
			Vect f5 = v6.cross(v5).getNorm();
			Vect f6 = v1.cross(v6).getNorm();
			Vect ans = (f1 + f2 + f3 + f4 + f5 + f6).getNorm();
			pVerts[n].nx = ans[X];
			pVerts[n].ny = ans[Y];
			pVerts[n].nz = ans[Z];
			normalArr[n][X] = ans[X];
			normalArr[n][Y] = ans[Y];
			normalArr[n][Z] = ans[Z];
		}
	}

	//Indices
	int tind = 0;
	for (int k = 0; k < heightMapW - 1; k++) {
		for (int l = 0; l < heightMapW - 1; l++) {
			pTriList[tind].set(l + (k * heightMapW), l + (k * heightMapW) + heightMapW, l + (k * heightMapW) + 1);
			tind++;
		}
	}
	for (int k = 0; k < heightMapW - 1; k++) {
		for (int l = 0; l < heightMapW - 1; l++) {
			pTriList[tind].set(l + (k * heightMapW) + heightMapW, l + (k * heightMapW) + heightMapW + 1, l + (k * heightMapW) + 1);
			tind++;
		}
	}

	//Cell Min-Max
	//int ncells = ntri / 2;
	MinMaxArr = new Vect[ntri];
	int mmind = 0;
	Vect min, max;
	for (int a = 0; a < heightMapW - 1; ++a) {
		for (int b = 0; b < heightMapW - 1; ++b) {
			min = pVerts[a + (b * imgWidth)].getV();
			max = pVerts[a + (b * imgWidth)].getV();
			int a1 = a + 1;
			int b1 = b + 1;
			if (pVerts[a1 + (b * imgWidth)].getV().Y() < min.Y()) min = pVerts[a1 + (b * imgWidth)].getV();
			if (pVerts[a1 + (b * imgWidth)].getV().Y() > max.Y()) max = pVerts[a1 + (b * imgWidth)].getV();
			if (pVerts[a1 + (b1 * imgWidth)].getV().Y() < min.Y()) min = pVerts[a1 + (b1 * imgWidth)].getV();
			if (pVerts[a1 + (b1 * imgWidth)].getV().Y() > max.Y()) max = pVerts[a1 + (b1 * imgWidth)].getV();
			if (pVerts[a + (b1 * imgWidth)].getV().Y() < min.Y()) min = pVerts[a + (b1 * imgWidth)].getV();
			if (pVerts[a + (b1 * imgWidth)].getV().Y() > max.Y()) max = pVerts[a + (b1 * imgWidth)].getV();

			min[X] = pVerts[a + (b * imgWidth)].getV().X();
			min[Z] = pVerts[a + (b * imgWidth)].getV().Z();
			max[X] = pVerts[a1 + (b1 * imgWidth)].getV().X();
			max[Z] = pVerts[a1 + (b1 * imgWidth)].getV().Z();

			MinMaxArr[mmind] = min;
			++mmind;
			MinMaxArr[mmind] = max;
			++mmind;
		}
	}

	pModel = new Model(pVerts, nverts, pTriList, ntri);

	N_TRI = ntri;
	N_VERTS = nverts;
	_BOTTOMBOUND = bottomBound;
	_LEN = len;
	_HGTW = heightMapW;

	delete[] pVerts;
	delete[] pTriList;
}

TerrainModel::~TerrainModel() {
	delete pModel;
	delete[] MinMaxArr;
	delete[] normalArr;
}

void TerrainModel::visualizeAABBs() {
	for (int i = 0; i < N_TRI; i = i + 2) {
		Vect min = MinMaxArr[i];
		Vect max = MinMaxArr[i+1];
		Visualizer::ShowAABB(min,max,XtremeColors::Green);
	}
}

void TerrainModel::identifyCell(float argX, float argZ) {
	int j = (int)((argX - _BOTTOMBOUND) / (_LEN / _HGTW));
	int i = (int)((argZ - _BOTTOMBOUND) / (_LEN / _HGTW));
	int k = (i + (j * (_HGTW - 1))) * 2;
	Vect min = MinMaxArr[k];
	Vect max = MinMaxArr[k + 1];
	Visualizer::ShowAABB(min, max, XtremeColors::Red);
}

Vect& TerrainModel::getNormal(float argX, float argZ) {
	int j = (int)((argX - _BOTTOMBOUND) / (_LEN / _HGTW));
	int i = (int)((argZ - _BOTTOMBOUND) / (_LEN / _HGTW));
	int k = (i + (j * (_HGTW)));
	if (k >= 0 && k < N_VERTS) return normalArr[k];
	else return normalArr[0];
}

void TerrainModel::identifyUnder(Vect& argmin, Vect& argmax) {

	float cX = argmin.X();
	float cZ = argmin.Z();
	//float dX = argmax.X() - argmin.X();
	//float dZ = argmax.Z() - argmin.Z();
	while (cX <= argmax.X()) {
		while (cZ <= argmax.Z()) {

			int j = (int)((cX - _BOTTOMBOUND) / (_LEN / _HGTW));
			int i = (int)((cZ - _BOTTOMBOUND) / (_LEN / _HGTW));
			int k = (i + (j * (_HGTW - 1))) * 2;
			Vect min = MinMaxArr[k];
			Vect max = MinMaxArr[k + 1];

			Visualizer::ShowAABB(min, max, XtremeColors::Red);

			cZ += 1;
		}
		cZ = argmin.Z();
		cX += 1;
	}
}

void TerrainModel::testCollision(Vect& argmin, Vect& argmax,Collidable* other) {

	float cX = argmin.X();
	float cZ = argmin.Z();
	//float dX = argmax.X() - argmin.X();
	//float dZ = argmax.Z() - argmin.Z();
	while (cX <= argmax.X()) {
		while (cZ <= argmax.Z()) {

			int j = (int)((cX - _BOTTOMBOUND) / (_LEN / _HGTW));
			int i = (int)((cZ - _BOTTOMBOUND) / (_LEN / _HGTW));
			int k = (i + (j * (_HGTW - 1))) * 2;
			Vect min = MinMaxArr[k];
			Vect max = MinMaxArr[k + 1];

			CollisionVolumeAABB tmpAABB;
			tmpAABB.ComputeData(max, min);

			if (XtremeMath::Intersect(tmpAABB, other->GetBSphere())) {
				if (XtremeMath::Intersect(tmpAABB, other->GetCollisionVolume())) {
					Visualizer::ShowAABB(min, max, XtremeColors::Red);
				}
				else {
					Visualizer::ShowAABB(min, max, XtremeColors::Green);
				}
			}
			else {
				Visualizer::ShowAABB(min, max, XtremeColors::Gray);
			}

			

			cZ += 1;
		}
		cZ = argmin.Z();
		cX += 1;
	}
}

//int TerrainModel::VertexIndex(int i, int j) {
//
//}
//
//int TerrainModel::PixelIndex(int i, int j) {
//
//}
//
//int TerrainModel::TriIndex(int i, int j) {
//
//}