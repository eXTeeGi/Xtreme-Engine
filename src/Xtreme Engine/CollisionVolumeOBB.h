#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "CollisionVolume.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB;

class CollisionVolumeOBB : public CollisionVolume
{
public:
	CollisionVolumeOBB();
	~CollisionVolumeOBB() {};
	CollisionVolumeOBB(const CollisionVolumeOBB&) = delete;
	CollisionVolumeOBB& operator= (const CollisionVolumeOBB&) = delete;

	virtual void ComputeData(Model* mod, const Matrix& mat);
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

#endif _CollisionVolumeOBB