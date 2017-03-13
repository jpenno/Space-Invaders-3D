#pragma once
#include <vector>
#include "Enemy.h"

class Shader;

class EnemyManager
{
private:
	std::vector<Enemy> m_enemys;

public:
	EnemyManager();
	~EnemyManager();

	void Spawn(int a_width, int a_height, int a_spacing, Shader *a_shader, Mesh *a_mesh );
	void Delete();
	
	void UpDate(float deltaTime);
	void Draw();
};

