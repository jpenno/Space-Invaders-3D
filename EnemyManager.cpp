#include "EnemyManager.h"
#include "Shader.h"
#include "Mesh.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Spawn(int a_width, int a_height, int a_spacing, Shader *a_shader, Mesh *a_mesh)
{
	for (int i = 0; i < a_width; i++)
	{
		for (int j = 0; j < a_height; j++)
		{
			Enemy enemy;
			enemy.m_position = glm::vec3(
				(i * a_spacing) - (a_width* a_spacing * 0.5f),
				1,
				(j * a_spacing) + 3);

			enemy.SetModel(a_shader, a_mesh);
			m_enemys.push_back(enemy);
		}
	}
}

void EnemyManager::Delete()
{
	m_enemys.clear();
}

void EnemyManager::UpDate(float deltaTime)
{

}

void EnemyManager::Draw()
{
	for (int i = 0; i < m_enemys.size(); i++)
	{
		m_enemys[i].Draw();
	}
}