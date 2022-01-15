#ifndef _CollisionDispatchBase
#define _CollisionDispatchBase

class Collidable;

class CollisionDispatchBase
{
public:
	virtual ~CollisionDispatchBase() {};

	virtual void ProcessCallbacks(Collidable*, Collidable*) = 0;
};

#endif _CollisionDispatchBase