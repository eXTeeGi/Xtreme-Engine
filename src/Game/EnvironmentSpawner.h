#ifndef _EnvironmentSpawner
#define _EnvironmentSpawner

#include <list>
#include "AzulCore.h"

class Die;
class Rock;

class EnvironmentSpawner {
public:
	EnvironmentSpawner();
	~EnvironmentSpawner();

	void generate();
	void generateBoss();
	void generateTutorial();
private:
	std::list<Die*> dieList;
	std::list<Rock*> rockList;
};

#endif _EnvironmentSpawner