
#ifndef _UFOObjectPool
#define _UFOObjectPool

#include <stack>
#include <list>

class UFO;

class UFOObjectPool
{
private:
	std::stack<UFO*> recycledItems;
	std::list<UFO*> activeItems;

public:
	UFOObjectPool();
	UFOObjectPool(const UFOObjectPool&) = delete;
	UFOObjectPool& operator=(const UFOObjectPool&) = delete;
	~UFOObjectPool();

	UFO* GetUFO();
	void ExitActive();

	void ReturnUFO(UFO* b);
};


#endif _UFOObjectPool
