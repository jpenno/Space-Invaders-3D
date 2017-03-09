#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera
{
private:
	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;
	float m_Roll = 0.0f;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;


	glm::vec3 m_up = glm::vec3(0, 1, 0);
	glm::vec3 m_Front = glm::vec3(0, 0, 1);
	
	glm::vec3 m_Postion = glm::vec3(3, 2, 0);

	int m_lastMouseXPos;
	int m_lastMouseYPos;

	float m_speed = 5.0f;

public:
	Camera();
	~Camera();
	void SetViewMatrix(glm::mat4 a_viewMatrix) { m_viewMatrix = a_viewMatrix; }
	void SetProjectionMatrix(glm::mat4 a_projectionMatrix) { m_projectionMatrix = a_projectionMatrix; }
	
	glm::mat4* GetViewMatrix() { return &m_viewMatrix; }
	glm::mat4* GetProjectionMatrix() { return &m_projectionMatrix; }


	glm::vec3 GetPoition() { return m_Postion; }
	void SetPoition(glm::vec3 a_Postion, glm::vec3  a_target);


	void SetSpeed(float a_speed) { m_speed = a_speed; }

	void Update(float deltaTime);
};