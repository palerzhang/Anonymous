#ifndef _ANONYMOUS_SHADER_
#define _ANONYMOUS_SHADER_

#include <glad\glad.h>
#include <unordered_map>

using namespace std;

typedef unordered_map<string, unsigned int> AsShaderCache;
typedef unordered_map<string, unsigned int>::iterator AsShaderCacheIter;
typedef pair<string, unsigned int> AsShaderCacheElement;

/*
\ Use to query compile and link status
*/
enum CompileType
{
	TYPE_VERTEX = 0,
	TYPE_FRAGMENT,
	TYPE_PROGRAM
};
/*
\ Shader class is used to manage shaders
\ Must configure vertex shader and fragment shader
*/
class AsShader
{
	/*
	\ vertex shader file name (no extension .vert)
	*/
	string mVertFile;
	/*
	\ fragment shader file name (no extension .frag)
	*/
	string mFragFile;
public:
	/*
	\ Constructor & deconstructor
	*/
	AsShader();
	~AsShader();
	/*
	\ Uniform setting functions
	\ Set uniform value after using program
	*/
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
	/*
	\ Set shader files, vertex file name and fragment file name
	\ @vertFile: vertex file name. 
	\	If @vertFile is empty, the vertex file name will not change
	\ @fragFile: fragment file name. 
	\	If @vertFile is empty, the fragment file name will not change
	\ This only works before compile shader
	*/
	void SetShaderFile(const string & vertFile, const string & fragFile);
	/*
	\ Prepare and process shaders (both vertex and fragment)
	\ Open file and read codes
	\ Compile codes
	\ Create and Link program
	\ Cache if is needed
	*/
	void PropareAndProcessShader();
	/*
	\ Use the shader program that this shader contains
	*/
	void Use();
	/*
	\ Get vertex shader file path
	*/
	inline string GetVertexShaderPath()
	{
		return AsShader::sVertexShaderDir + mVertFile + ".vert";
	}
	/*
	\ Get fragment shader file path
	*/
	inline string GetFragmentShaderPath()
	{
		return AsShader::sFragmentShaderDir + mFragFile + ".frag";
	}
	/*
	\ Combine vertex and fragment shader file name as key of cache
	*/
	inline string GetShaderKeyStr()
	{
		return mVertFile + ":" + mFragFile;
	}
	/*
	\ Check compile states of vertex and fragment shader 
	\ and link states of program
	*/
	static void CheckCompileStates(unsigned int shaderId, CompileType type);
	/*
	\ Vertex shader directory
	*/
	static string sVertexShaderDir;
	/*
	\ Fragment shader directory
	*/
	static string sFragmentShaderDir;
private:
	/*
	\ Program id
	*/
	unsigned int mID;
	/*
	\ Cache of shader programs
	*/
	static AsShaderCache sShaderCache;
};

#endif