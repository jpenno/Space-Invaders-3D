#include "Model.h"
#include "gl_core_4_4.h"
#include <glm/ext.hpp>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"


#include <iostream>


Model::Model()
{
	//texture = new aie::Texture(".WhiteTexture.bmp");
}


Model::~Model()
{
	//if (texture != nullptr)
	//	delete texture;
}

void Model::SetPostion(glm::mat4 a_position)
{
	m_position = a_position;
}

void Model::SetScale(glm::vec3 a_scale)
{

}

void Model::SetMesh(Mesh &a_mesh)
{
	m_meshReff = &a_mesh;
}

void Model::SetShader(Shader *a_shader)
{
	m_shader = a_shader;
}

void Model::Draw()
{
	glm::vec3 a_color = glm::vec3(1, 1, 1);

	if (m_shader != nullptr )
	{
		m_shader->Draw(m_position);

		m_meshReff->Draw();
	}
	else
	{
		std::cout << "Shader Not Set" << std::endl;
	}

	glUseProgram(0);
}
