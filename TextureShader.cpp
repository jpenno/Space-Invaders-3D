#include "TextureShader.h"
#include "Texture.h"
#include "gl_core_4_4.h"
#include <iostream>

TextureShader::TextureShader()
{
}


TextureShader::~TextureShader()
{
}

void TextureShader::LoadFromFile(const char* a_vsFilePath, const char* a_fsFilePath)
{
	Load(a_vsFilePath, a_fsFilePath);

	AddAttribute("vPosition");
	AddAttribute("vColor");
	AddAttribute("vuv");
	AddAttribute("vNormal");

	m_texture = new aie::Texture("WhiteTexture.png");
}

void TextureShader::SetTextureHandel(unsigned int *a_textureHandel)
{
	m_textureHandel = a_textureHandel;
}

void TextureShader::Draw(glm::mat4 a_postion)
{
	Shader::Draw(a_postion);
	
	glUniform3fv(glGetUniformLocation(m_shader, "color"), 1, &m_color[0]);
	


	// send the textures
	glActiveTexture(GL_TEXTURE0);
	if (m_textureHandel != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, *m_textureHandel);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_texture->getHandle());
	}
	glUniform1i(glGetUniformLocation(m_shader, "texture"), 0);
}

