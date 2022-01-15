#ifndef _ShaderManager
#define _ShaderManager

#include <unordered_map>
#include "AzulCore.h"
using namespace std;

class ShaderManager
{
	friend class ShaderManagerAttorney;
public:
	static ShaderManager* ptrinstance;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a shader object* using the given key. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey">	The key/name of the shader to get. </param>
	///
	/// <returns>	Null if it fails, else a pointer to a ShaderObject. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static ShaderObject* Get(const string& argKey);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Loads a shader from a given file path. </summary>
	///
	/// <remarks>	Jakei, 3/2/2020. </remarks>
	///
	/// <param name="argKey"> 	The name/key you want to give the shader. </param>
	/// <param name="argPath">	Full pathname of the shader file. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void Load(const string& argKey, const char * const argPath);

private:
	static ShaderManager& Instance() {
		if (!ptrinstance)
			ptrinstance = new ShaderManager;
		return *ptrinstance;
	}

	ShaderManager();
	~ShaderManager() {};
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator= (const ShaderManager&) = delete;

	static void Delete();
	void privDelete();
	ShaderObject* privGet(const string& argKey);
	void privLoad(const string& argKey, const char* const argPath);

	unordered_map<string, ShaderObject*> shaderMap;
};

#endif _ShaderManager