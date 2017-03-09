#define GLM_SWIZZLE
#include "Player.h"
#include "Input.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>


Player::Player()
{
}


Player::~Player()
{
}


void Player::SetModel(Shader *a_shader, Mesh *a_mesh)
{
	m_model.SetMesh(*a_mesh);
	m_model.SetShader(a_shader);
	glm::mat4 position = glm::mat4{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		m_position.x, m_position.y, m_position.z, 1
	};


	m_model.SetPostion(position);
}

void Player::UpDate(float a_deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_position.x += m_speed * a_deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_position.x -= m_speed * a_deltaTime;


	glm::mat4 position = glm::mat4{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		m_position.x, m_position.y, m_position.z, 1
	};
	m_model.SetPostion(position);
}

void Player::Draw()
{
	m_model.Draw();
}
