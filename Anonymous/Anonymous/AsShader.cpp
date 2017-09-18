#include "AsShader.h"
#include <string>

string TypeName[3] = 
{
	"Vertex Shader",
	"Fragment Shader",
	"Program"
};

AsShader::AsShader()
{
	mID = -1;
	mVertFile = "Shader\\vertex\\default2d.vert";
	mFragFile = "Shader\\fragment\\default2d.frag";
}

AsShader::~AsShader()
{
	// Nothing yet
}

void AsShader::SetShaderFile(const string & vertFile, const string & fragFile)
{
	mVertFile = vertFile;
	mFragFile = fragFile;
}

void AsShader::PropareAndProcessShader()
{
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(mVertFile);
		fShaderFile.open(mFragFile);
		stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// shader Program
	mID = glCreateProgram();
	glAttachShader(mID, vertex);
	glAttachShader(mID, fragment);
	glLinkProgram(mID);
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void AsShader::Use()
{
	glUseProgram(mID);

	int id = glGetUniformLocation(mID, "_Color");
}

void AsShader::CheckCompileStates(unsigned int shaderId, CompileType type)
{
	int success = 1;
	char infoLog[1024];
	switch (type)
	{
	case CompileType::TYPE_PROGRAM:
	{
		glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderId, 1024, NULL, infoLog);
			cout << "ERROR::PROGRAM_LINKING_ERROR of type: " + TypeName[type] + "\n"
				<< infoLog
				<< "\n -- --------------------------------------------------- -- \n";
		}
	}
		break;
	case CompileType::TYPE_VERTEX:
	case CompileType::TYPE_FRAGMENT:
	{
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderId, 1024, NULL, infoLog);
			cout << "ERROR::SHADER_COMPILATION_ERROR of type: " + TypeName[type] + "\n"
				<< infoLog
				<< "\n -- --------------------------------------------------- -- \n";
		}
	}
		break;
	}
	if (success)
		cout << "SUCCESS\n";
}