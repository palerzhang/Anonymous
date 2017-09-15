#ifndef _ANONYMOUS_SHADER_
#define _ANONYMOUS_SHADER_

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

enum CompileType
{
	TYPE_VERTEX = 0,
	TYPE_FRAGMENT,
	TYPE_PROGRAM
};

class AsShader
{
public:
	AsShader();
	~AsShader();

	inline void SetBool(const char * name, bool value) const;
	inline void SetInt(const char * name, int value) const;
	inline void SetFloat(const char * name, float value) const;
	inline void SetUint(const char * name, unsigned int value) const;
	inline void SetFloat3(const char * name, float value0, float value1, float value2) const;
	inline void SetFloat4(const char * name, float value0, float value1, float value2, float value3) const;
	inline void SetFloat3v(const char * name, const float * vec) const;
	inline void SetFloat4v(const char * name, const float * vec) const;
	inline void SetMatrix4x4(const char * name) const;

	void PropareAndProcessShader(const char * vertexFile, const char * fragmentFille);
	inline void Use();

	static void CheckCompileStates(unsigned int shaderId, CompileType type);
private:
	unsigned int mID;
};

#endif