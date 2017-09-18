#ifndef _ANONYMOUS_SHADER_
#define _ANONYMOUS_SHADER_

#include <fstream>
#include <sstream>
#include <iostream>
#include <glad\glad.h>

using namespace std;

enum CompileType
{
	TYPE_VERTEX = 0,
	TYPE_FRAGMENT,
	TYPE_PROGRAM
};

class AsShader
{
	string mVertFile;
	string mFragFile;
public:
	AsShader();
	~AsShader();

	inline void SetBool(const char * name, bool value) const
	{
		glUniform1i(glGetUniformLocation(mID, name), (int)value);
	}
	inline void SetInt(const char * name, int value) const
	{
		glUniform1i(glGetUniformLocation(mID, name), value);
	}
	inline void SetFloat(const char * name, float value) const
	{
		glUniform1f(glGetUniformLocation(mID, name), value);
	}
	inline void SetUint(const char * name, unsigned int value) const
	{
		glUniform1ui(glGetUniformLocation(mID, name), value);
	}
	inline void SetFloat3(const char * name, float value0, float value1, float value2) const
	{
		glUniform3f(glGetUniformLocation(mID, name), value0, value1, value2);
	}
	inline void SetFloat4(const char * name, float value0, float value1, float value2, float value3) const
	{
		glUniform4f(glGetUniformLocation(mID, name), value0, value1, value2, value3);
	}
	inline void SetFloat3v(const char * name, const float * vec) const
	{
		glUniform3fv(glGetUniformLocation(mID, name), 3, vec);
	}
	inline void SetFloat4v(const char * name, const float * vec) const
	{
		glUniform3fv(glGetUniformLocation(mID, name), 4, vec);
	}
	inline void SetMatrix4x4(const char * name) const
	{}

	void SetShaderFile(const string & vertFile, const string & fragFile);
	void PropareAndProcessShader();
	void Use();

	static void CheckCompileStates(unsigned int shaderId, CompileType type);
private:
	unsigned int mID;
};

#endif