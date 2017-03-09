#include "DiffuseShader.h"
#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include "gl_core_4_4.h"


DiffuseShader::DiffuseShader()
{
}

DiffuseShader::~DiffuseShader()
{
}

void DiffuseShader::LoadFromFile(const char* a_vsFilePath, const char* a_fsFilePath)
{
	Load(a_vsFilePath, a_fsFilePath);

	AddAttribute("vPosition");
	AddAttribute("vColor");
	AddAttribute("vuv");
	AddAttribute("vNormal");
}

void DiffuseShader::Draw(glm::mat4 a_postion)
{
	Shader::Draw(a_postion);
}

