#include "Enemy.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::SetModel(Shader *a_shader, Mesh *a_mesh)
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

void Enemy::UpDate(float a_deltaTime)
{

}

void Enemy::Draw()
{
	m_model.Draw();
}
