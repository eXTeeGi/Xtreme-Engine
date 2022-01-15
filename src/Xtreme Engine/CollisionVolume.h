#ifndef _CollisionVolume
#define _CollisionVolume

#include "AzulCore.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolume
{
public:
	CollisionVolume() {};
	virtual ~CollisionVolume() {};
	CollisionVolume(const CollisionVolume&) = delete;
	CollisionVolume& operator= (const CollisionVolume&) = delete;

	virtual void ComputeData(Model* mod, const Matrix& mat) = 0;
	virtual void DebugView(const Vect& col) const  = 0;

	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;

	/*virtual const Vect& GetCenter() const = 0;
	virtual float GetRadius() const = 0;
	virtual const Vect& getCornerMax() const = 0;
	virtual const Vect& getCornerMin() const = 0;*/
};

#endif _CollisionVolume