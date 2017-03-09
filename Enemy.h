#pragma once
#include "Model.h"

class Enemy
{
private:
	Model m_model;
	float m_speed = 50.0f;

public:
	Enemy();
	~Enemy();

	glm::vec3 m_position = glm::vec3(0, 1, 0);

	void SetModel(Shader *a_shader, Mesh *a_mesh);
	void UpDate(float a_deltaTime);
	void Draw();
};