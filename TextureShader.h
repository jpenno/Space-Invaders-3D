#pragma once
#include "Shader.h"
#include <glm/vec3.hpp>


namespace aie 
{
	class Texture;
};

class TextureShader : public Shader
{
private:
	aie::Texture *m_texture;
	glm::vec3 m_color = glm::vec3(1, 0, 1);

	unsigned int *m_textureHandel = nullptr;

public:
	TextureShader();
	~TextureShader();

	void SetColro(glm::vec3 a_color) { m_color = a_color; }

	void SetTextureHandel(unsigned int *a_textureHandel);
	virtual void Draw(glm::mat4 a_postion) override;
	virtual void LoadFromFile(const char* a_vsFilePath, const char* a_fsFilePath) override;
};

