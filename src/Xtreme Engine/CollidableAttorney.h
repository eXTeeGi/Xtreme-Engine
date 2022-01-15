#ifndef _CollidableAttorney
#define _CollidableAttorney

#include "Collidable.h"

class CollidableAttorney
{
public:
	class GameLoop
	{
		friend class CollidableManager;
		friend class TerrainObject;
	private:
		static void CollisionTerrain(Collidable* pMgr) { pMgr->CollisionTerrain(); }
	};

public:
	class Registration
	{
		friend class CollisionRegistrationCommand;
		friend class CollisionDeregistrationCommand;
	private:
		static void SceneRegistration(Collidable* pMgr) { pMgr->SceneRegistration(); }
		static void SceneDeregistration(Collidable* pMgr) { pMgr->SceneDeregistration(); }
	};
};


#endif _CollidableAttorney