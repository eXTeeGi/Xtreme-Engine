#ifndef _AlarmableManager
#define _AlarmableManager

#include <map>

using namespace std;

class Alarmable;

class AlarmableManager
{
public:
	AlarmableManager();
	~AlarmableManager();
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator= (const AlarmableManager&) = delete;

	enum ALARM_ID { ALARM_0, ALARM_1, ALARM_2 };
	static const int ALARM_NUMBER = 3;
private:
	using AlarmEvent = std::pair< Alarmable*, ALARM_ID>;
	using StorageMap = std::multimap<float, AlarmEvent>;
	StorageMap storageMap;



public:


	using StorageMapRef = StorageMap::iterator;

	void Deregister( StorageMapRef&);
	void ProcessAlarms();
	void Register(float, Alarmable*, ALARM_ID, StorageMapRef&);
private:
	
	

};

#endif _AlarmableManager