#ifndef _ModelManager
#define _ModelManager

#include <unordered_map>
#include "AzulCore.h"
using namespace std;

class ModelManager
{
	friend class ModelManagerAttorney;
public:
	static ModelManager* ptrinstance;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the model of the given name/key. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey">	The name/key of the model. </param>
	///
	/// <returns>	Null if it fails, else a pointer to a Model. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static Model* Get(const string& argKey);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Loads and stores a model from a file path. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey"> 	The name/key you want to give the model. </param>
	/// <param name="argPath">	The file patch of the model file. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void Load(const string& argKey, const char* const argPath);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Loads and stores a model from premade models. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey">	The name/key you want to give the model. </param>
	/// <param name="argPMM">	The premade model. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void Load(const string& argKey, const Model::PreMadeModels argPMM);

private:
	static ModelManager& Instance() {
		if (!ptrinstance)
			ptrinstance = new ModelManager;
		return *ptrinstance;
	}

	ModelManager();
	~ModelManager() {};
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator= (const ModelManager&) = delete;

	static void Delete();
	void privDelete();
	Model* privGet(const string& argKey);
	void privLoad(const string& argKey, const char* const argPath);
	void privLoad(const string& argKey, const Model::PreMadeModels argPMM);

	unordered_map<string, Model*> modelMap;
};

#endif _ModelManager