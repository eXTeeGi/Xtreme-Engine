#include "CollisionVolumeBSphere.h"
#include "XtremeMath.h"
#include "Visualizer.h"

CollisionVolumeBSphere::CollisionVolumeBSphere() {
	Center = Vect(0, 0, 0);
	Radius = 1;
}

void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat) {
	
	//Too proud to delete
	/*float rangeX, rangeY, rangeZ, minRange;
	rangeX = mod->getMaxAABB().X() - mod->getMinAABB().X();
	minRange = rangeX;
	rangeY = mod->getMaxAABB().Y() - mod->getMinAABB().Y();
	if (rangeY < minRange) minRange = rangeY;
	rangeZ = mod->getMaxAABB().Z() - mod->getMinAABB().Z();
	if (rangeZ < minRange) minRange = rangeZ;

	Radius = minRange / 2;
	float cX = (mod->getMaxAABB().X() + mod->getMinAABB().X()) / 2;
	float cY = (mod->getMaxAABB().Y() + mod->getMinAABB().Y()) / 2;
	float cZ = (mod->getMaxAABB().Z() + mod->getMinAABB().Z()) / 2;
	Center = {cX,cY,cZ};

	Vect* v1 = mod->getVectList();
	for (int i = 0;i < mod->getVectNum();i++) {
		Vect v = *(v1 + i);
		Vect between = Center - v;
		float distance = XtremeMath::EuclideanNorm(between);
		if (distance > Radius) {
			float delta = (distance - Radius) / 2;
			Radius = Radius + delta;
			cX = Center.X() + delta * v.X() / XtremeMath::EuclideanNorm(v);
			cY = Center.Y() + delta * v.Y() / XtremeMath::EuclideanNorm(v);
			cZ = Center.Z() + delta * v.Z() / XtremeMath::EuclideanNorm(v);
			Center = { cX,cY,cZ };
		}
	}
	Center *= mat;
	Radius *= XtremeMath::EuclideanNorm(Vect(mat.M0(),mat.M1(),mat.M2(),mat.M3()));*/
	Radius = mod->getRadius() * XtremeMath::EuclideanNorm(Vect(mat.M0(), mat.M1(), mat.M2(), mat.M3()));
	Center = mod->getCenter() * mat;
}

void CollisionVolumeBSphere::DebugView(const Vect& col) const {
	Visualizer::ShowBSphere(*this, col);
}

//bool CollisionVolumeBSphere::intersect(const CollisionVolumeBSphere& other) {
//	Vect between = this->Center - other.Center;
//	float distance = between.dot(between);
//
//	float rSquared = (this->Radius + other.Radius) * (this->Radius + other.Radius);
//
//	return distance <= rSquared;
//}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const {
	return other.IntersectVisit(*this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const {
	return XtremeMath::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const {
	return XtremeMath::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const {
	return XtremeMath::Intersect(*this, other);
}

const Vect& CollisionVolumeBSphere::GetCenter() const {
	return Center;
}
float CollisionVolumeBSphere::GetRadius() const {
	return Radius;
}