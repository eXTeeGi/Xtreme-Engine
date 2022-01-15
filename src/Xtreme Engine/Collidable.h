#ifndef _Collidable
#define _Collidable

#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "Scene.h"
#include "Visualizer.h"

class CollisionRegistrationCommand;
class CollisionDeregistrationCommand;
class CollisionVolumeBSphere;
class CollisionVolume;

class Collidable
{
	friend class CollidableAttorney;
private:
	CollisionManager::PWTypeID myID = CollisionManager::PWID_UNDEFINED;

	CollisionRegistrationCommand* pRegCmd;
	CollisionDeregistrationCommand* pDeregCmd;

	enum class RegistrationState
	{
		CURRENTLY_DEREGISTERED,
		PENDING_REGISTRATION,
		CURRENTLY_REGISTERED,
		PENDING_DEREGISTRATION
	};
	RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

	CollidableGroup::CollidableCollectionRef pMyDeleteRef;

	CollisionVolume* ColVolume = nullptr;
	CollisionVolume* ColBSphere = nullptr;
	CollisionVolume* ColAABB = nullptr;
	CollisionVolume* ColOBB = nullptr;
	Model* pColModel;
	
	virtual void CollisionTerrain() {};
	
	
protected:
	template < typename C>
	void SetCollidableGroup()
	{
		myID = SceneManager::GetCurrentScene()->GetCollisionManager()->GetTypeID<C>();
	}

	enum class VolumeType {
		BSPHERE,
		AABB,
		OBB
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Select the collision volume to use for processing. </summary>
	///
	/// <param name="mod">	The model of the collidable. </param>
	/// <param name="VT">	The desired collision volume: BSPHERE, AABB, or OBB </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetColliderModel(Model* mod, VolumeType VT);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Update the world matrix of the collision volume. Should be done whenever it moves. </summary>
	///
	/// <param name="mat">	The world matrix of the collidable. </param>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void UpdateCollisionData(const Matrix& mat);

	Collidable();
	~Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator= (const Collidable&) = delete;

	void SceneDeregistration();
	void SceneRegistration();
public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit deregistration from the collision system. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitCollisionDeregistration();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit registration to the collision system. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitCollisionRegistration();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the user defined collision volume. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <returns>	The volume. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	const CollisionVolume& GetCollisionVolume();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the internal bsphere. </summary>
	///
	/// <remarks>	Jakei, 6/7/2020. </remarks>
	///
	/// <returns>	The b sphere. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	const CollisionVolume& GetBSphere();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Returns whether the collidable is registered for collision. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <returns>	A bool. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool isRegistered();


	
};

#endif _Collidable