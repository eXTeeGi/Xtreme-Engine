#include "CollisionVolumeOBB.h"
#include "XtremeMath.h"
#include "Visualizer.h"

CollisionVolumeOBB::CollisionVolumeOBB() {
	CornerMax = { 0,0,0 };
	CornerMin = { 0,0,0 };
}

void CollisionVolumeOBB::ComputeData(Model* mod, const Matrix& mat) {
	CornerMin = mod->getMinAABB();
	CornerMax = mod->getMaxAABB();

	halfDiagonal = { (CornerMax[X] - CornerMin[X]) / 2,(CornerMax[Y] - CornerMin[Y]) / 2 ,(CornerMax[Z] - CornerMin[Z]) / 2 };
	Center = (CornerMin + halfDiagonal) * mat;
	scaleSquared = (halfDiagonal.getNorm() * XtremeMath::EuclideanNorm(mat.get(ROW_0))).magSqr();
	W = mat;
}

void CollisionVolumeOBB::DebugView(const Vect& col) const {
	Visualizer::ShowOBB(*this, col);
}

bool CollisionVolumeOBB::IntersectAccept(const CollisionVolume& other) const {
	return other.IntersectVisit(*this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const {
	return XtremeMath::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const {
	return XtremeMath::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const {
	return XtremeMath::Intersect(*this, other);
}

const Vect& CollisionVolumeOBB::getCornerMin() const {
	return CornerMin;
}

const Vect& CollisionVolumeOBB::getCornerMax() const {
	return CornerMax;
}

const Vect& CollisionVolumeOBB::getHalfDiagonal() const {
	return halfDiagonal;
}

const Vect& CollisionVolumeOBB::getCenter() const {
	return Center;
}

const float CollisionVolumeOBB::getScaleSquared() const {
	return scaleSquared;
}

const Matrix& CollisionVolumeOBB::getW() const {
	return W;
}