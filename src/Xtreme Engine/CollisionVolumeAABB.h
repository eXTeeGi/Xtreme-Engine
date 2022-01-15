#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "CollisionVolume.h"

class CollisionVolumeBSphere;
class CollisionVolumeOBB;

class CollisionVolumeAABB : public CollisionVolume
{
public:
	CollisionVolumeAABB();
	~CollisionVolumeAABB() {};
	CollisionVolumeAABB(const CollisionVolumeAABB&) = delete;
	CollisionVolumeAABB& operator= (const CollisionVolumeAABB&) = delete;

	virtual void ComputeData(Model* mod, const Matrix& mat);
	virtual void ComputeData(CollisionVolumeBSphere& bs);
	virtual void ComputeData(Vect& max, Vect& min);
	virtual void DebugView(const Vect& col) const;

	virtual bool IntersectAccept(const CollisionVolume& other) const;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const;

	const Vect& getCornerMax() const;
	const Vect& getCornerMin() const;
	const Vect& getHalfDiagonal() const;
	const Vect& getCenter() const;
	const float getScaleSquared() const;
	const Matrix& getW() const;

private:
	Matrix W;
	Vect CornerMax;
	Vect CornerMin;
	Vect halfDiagonal;
	Vect Center;
	float scaleSquared;
};

#endif _CollisionVolumeAABB