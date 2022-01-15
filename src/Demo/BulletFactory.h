

#ifndef _BulletFactory
#define _BulletFactory

#include "BulletObjectPool.h"
#include "Matrix.h"
class GameObject;
class Matrix;
class Vect;

class BulletFactory
{
private:
	BulletFactory() = default;												
	BulletFactory(const BulletFactory&) = delete;				
	BulletFactory& operator=(const BulletFactory&) = delete;	
	~BulletFactory() = default;									

	static BulletFactory* ptrInstance;
	static BulletFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BulletFactory();
		return *ptrInstance;
	};

	BulletObjectPool myBulletPool;  

	void privCreateBullet(Matrix, Matrix, Vect);
	void privRecycleBullet(GameObject* b);

	int maxAmmo = 100;
	int ammo = maxAmmo;

public:

	static void CreateBullet(Matrix a, Matrix b, Vect c) { Instance().privCreateBullet(a,b,c); };
	static void RecycleBullet(GameObject* b) { Instance().privRecycleBullet(b); };

	static void Terminate();
};


#endif _BulletFactory