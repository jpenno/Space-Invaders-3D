#include "Shader.h"
#include "gl_core_4_4.h"
#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace std;

Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::Set(glm::mat4 &a_viewMatrix, glm::mat4 &a_projectionMatrix)
{
	m_viewMatrix = &a_viewMatrix;
	m_projectionMatrix = &a_projectionMatrix;
}

void Shader::Draw(glm::mat4 a_postion)
{
	glUseProgram(m_shader);
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "projection"), 1, false, glm::value_ptr(*m_projectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "view"), 1, false, glm::value_ptr(*m_viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "model"), 1, false, glm::value_ptr(a_postion));
}

void Shader::LoadFromFile(const char * a_vsFilePath, const char * a_fsFilePath)
{
	std::string vsSource = StringFromFile(a_vsFilePath);
	const char *vsShaderSrcPtr = vsSource.c_str();

	std::string fsSource = StringFromFile(a_fsFilePath);
	const char *fsShaderSrcPtr = fsSource.c_str();

	// Step 1:
	// Load the vertex shader, provide it with the source code and compile it.
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsShaderSrcPtr, NULL);
	glCompileShader(vs);

	// Step 2:
	// Load the fragment shader, provide it with the source code and compile it.
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsShaderSrcPtr, NULL);
	glCompileShader(fs);


	// Step 3:
	// Create the shader program
	m_shader = glCreateProgram();

	glAttachShader(m_shader, vs);
	glAttachShader(m_shader, fs);

	glLinkProgram(m_shader);

	// Step 6:
	// destroy the vertex and fragment shader, we are finished with them
	// as they have been combined into the shaderProgram
	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shader::AddAttribute(char * a_attributeName)
{
	glBindAttribLocation(m_shader, attributeIndex, a_attributeName);
	attributeIndex++;
}

void Shader::Delete()
{
	glDeleteProgram(m_shader);
}


unsigned int Shader::GetShader()
{
	return m_shader;
}

std::string Shader::StringFromFile(const char * a_filename)
{
	std::ifstream file(a_filename);
	std::string fileString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return fileString;
}

void Shader::Load(const char* a_vsFilePath, const char* a_fsFilePath)
{
	std::string vsSource = StringFromFile(a_vsFilePath);
	const char *vsShaderSrcPtr = vsSource.c_str();

	std::string fsSource = StringFromFile(a_fsFilePath);
	const char *fsShaderSrcPtr = fsSource.c_str();

	// Step 1:
	// Load the vertex shader, provide it with the source code and compile it.
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsShaderSrcPtr, NULL);
	glCompileShader(vs);

	// Step 2:
	// Load the fragment shader, provide it with the source code and compile it.
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsShaderSrcPtr, NULL);
	glCompileShader(fs);


	// Step 3:
	// Create the shader program
	m_shader = glCreateProgram();

	glAttachShader(m_shader, vs);
	glAttachShader(m_shader, fs);

	glLinkProgram(m_shader);

	// Step 6:
	// destroy the vertex and fragment shader, we are finished with them
	// as they have been combined into the shaderProgram
	glDeleteShader(vs);
	glDeleteShader(fs);
}
