#ifndef _PowerupManager
#define _PowerupManager


class PowerupManager
{
public:
	static PowerupManager* ptrinstance;

	static void speedBoost();

	static int getProbability() { return Instance().powerupProbability; }
	static void addProbability() { ++Instance().powerupProbability; }
	static void subProbability() { if (Instance().powerupProbability > 1) --Instance().powerupProbability; }

	static void Terminate() { Instance().privTerminate(); }
private:
	PowerupManager();

	static PowerupManager& Instance() {
		if (!ptrinstance)
			ptrinstance = new PowerupManager;
		return *ptrinstance;
	}

	void privTerminate();

	int powerupProbability;
};

#endif _PowerupManager