#pragma once
#include <string>
#include <glm/mat4x4.hpp>

class Shader
{
public:
	Shader();
	virtual ~Shader();

	void Set(glm::mat4 &a_viewMatrix, glm::mat4 &a_projectionMatrix);

	virtual void Draw(glm::mat4 a_postion);

	virtual void Delete();

	unsigned int GetShader();
	


protected:
	std::string StringFromFile(const char* a_filename);
	void Load(const char* a_vsFilePath, const char* a_fsFilePath);
	virtual void LoadFromFile(const char* a_vsFilePath, const char* a_fsFilePath);


	glm::mat4 *m_viewMatrix = nullptr;
	glm::mat4 *m_projectionMatrix = nullptr;


	void AddAttribute(char* a_attributeName);

	unsigned int attributeIndex = 0;
	unsigned int shader;

	const char* m_vertxShader;
	const char* m_fragmentShader;

	unsigned int m_shader;
};