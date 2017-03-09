#pragma once
#include "Shader.h"

class DiffuseShader : public Shader
{
private:


public:
	DiffuseShader();
	~DiffuseShader();

	virtual void LoadFromFile(const char* a_vsFilePath, const char* a_fsFilePath) override;

	virtual void Draw(glm::mat4 a_postion) override;
};

