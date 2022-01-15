#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "XtremeMath.h"
#include "Visualizer.h"

CollisionVolumeAABB::CollisionVolumeAABB() {
	CornerMax = { 0,0,0 };
	CornerMin = { 0,0,0 };
}

void CollisionVolumeAABB::ComputeData(CollisionVolumeBSphere& bs) {
	CornerMax[X] = bs.GetCenter().X() + bs.GetRadius();
	CornerMax[Y] = bs.GetCenter().Y() + bs.GetRadius();
	CornerMax[Z] = bs.GetCenter().Z() + bs.GetRadius();
	CornerMin[X] = bs.GetCenter().X() - bs.GetRadius();
	CornerMin[Y] = bs.GetCenter().Y() - bs.GetRadius();
	CornerMin[Z] = bs.GetCenter().Z() - bs.GetRadius();

	W = Matrix(TRANS, bs.GetCenter());

	Vect CMaxLocal = CornerMax * W.getInv();
	Vect CMinLocal = CornerMin * W.getInv();
	halfDiagonal = { (CMaxLocal[X] - CMinLocal[X]) / 2,(CMaxLocal[Y] - CMinLocal[Y]) / 2 ,(CMaxLocal[Z] - CMinLocal[Z]) / 2 };
	Center = (CMinLocal + halfDiagonal) * W;
	scaleSquared = (halfDiagonal.getNorm() * XtremeMath::EuclideanNorm(W.get(ROW_0))).magSqr();
}

void CollisionVolumeAABB::ComputeData(Vect& max, Vect& min) {
	CornerMax = max;
	CornerMin = min;

	W = Matrix(TRANS, {(max.X() + min.X()) / 2,(max.Y() + min.Y()) / 2 ,(max.Z() + min.Z()) / 2 });

	Vect CMaxLocal = CornerMax * W.getInv();
	Vect CMinLocal = CornerMin * W.getInv();
	halfDiagonal = { (CMaxLocal[X] - CMinLocal[X]) / 2,(CMaxLocal[Y] - CMinLocal[Y]) / 2 ,(CMaxLocal[Z] - CMinLocal[Z]) / 2 };
	Center = (CMinLocal + halfDiagonal) * W;
	scaleSquared = (halfDiagonal.getNorm() * XtremeMath::EuclideanNorm(W.get(ROW_0))).magSqr();
}

void CollisionVolumeAABB::ComputeData(Model* mod, const Matrix& mat) {
	Vect* vertList = mod->getVectList();
	int vertNum = mod->getVectNum();
	Vect currVert = vertList[0] * mat;

	CornerMax[X] = currVert.X();
	CornerMax[Y] = currVert.Y();
	CornerMax[Z] = currVert.Z();
	CornerMin[X] = currVert.X();
	CornerMin[Y] = currVert.Y();
	CornerMin[Z] = currVert.Z();

	for (int i = 1; i < vertNum; ++i) {
		currVert = vertList[i] * mat;
		if (currVert.X() > CornerMax.X()) CornerMax[X] = currVert.X();
		if (currVert.Y() > CornerMax.Y()) CornerMax[Y] = currVert.Y();
		if (currVert.Z() > CornerMax.Z()) CornerMax[Z] = currVert.Z();
		if (currVert.X() < CornerMin.X()) CornerMin[X] = currVert.X();
		if (currVert.Y() < CornerMin.Y()) CornerMin[Y] = currVert.Y();
		if (currVert.Z() < CornerMin.Z()) CornerMin[Z] = currVert.Z();
	}
	
	Vect CMaxLocal = CornerMax * mat.getInv();
	Vect CMinLocal = CornerMin * mat.getInv();
	halfDiagonal = { (CMaxLocal[X] - CMinLocal[X]) / 2,(CMaxLocal[Y] - CMinLocal[Y]) / 2 ,(CMaxLocal[Z] - CMinLocal[Z]) / 2 };
	Center = (CMinLocal + halfDiagonal) * mat;
	scaleSquared = (halfDiagonal.getNorm() * XtremeMath::EuclideanNorm(mat.get(ROW_0))).magSqr();
	W = mat;

	//CornerMax *= mat;
	//CornerMin *= mat;
}

void CollisionVolumeAABB::DebugView(const Vect& col) const {
	Visualizer::ShowAABB(*this, col);
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const {
	return other.IntersectVisit(*this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const {
	return XtremeMath::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const {
	return XtremeMath::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& other) const {
	return XtremeMath::Intersect(*this, other);
}

const Vect& CollisionVolumeAABB::getCornerMin() const {
	return CornerMin;
}

const Vect& CollisionVolumeAABB::getCornerMax() const {
	return CornerMax;
}

const Vect& CollisionVolumeAABB::getHalfDiagonal() const {
	return halfDiagonal;
}

const Vect& CollisionVolumeAABB::getCenter() const {
	return Center;
}

const float CollisionVolumeAABB::getScaleSquared() const {
	return scaleSquared;
}

const Matrix& CollisionVolumeAABB::getW() const {
	return W;
}