#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "CollisionVolume.h"

class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolumeBSphere: public CollisionVolume
{
public:
	 CollisionVolumeBSphere();
	 ~CollisionVolumeBSphere() {};
	 CollisionVolumeBSphere(const CollisionVolumeBSphere&) = delete;
	 CollisionVolumeBSphere& operator= (const CollisionVolumeBSphere&) = delete;

	virtual void ComputeData(Model* mod, const Matrix& mat);
	virtual void DebugView(const Vect& col) const;

	virtual bool IntersectAccept(const CollisionVolume& other) const;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const;

	const Vect& GetCenter() const;
	float GetRadius() const;

private:
	Vect Center;
	float Radius;
};

#endif _CollisionVolumeBSphere