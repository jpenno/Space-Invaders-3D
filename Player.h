#pragma once
#include <glm/vec3.hpp>
#include "Model.h"

class Shader;
class Mesh;

class Player
{
private:
	Model m_model;
	float m_speed = 50.0f;


public:
	Player();
	~Player();

	glm::vec3 m_position = glm::vec3(0, 1, 0);
	glm::vec3 m_CameraOffSet = glm::vec3(0, 2, -5);

	void SetModel(Shader *a_shader, Mesh *a_mesh);


	void UpDate(float a_deltaTime);

	void Draw();
};