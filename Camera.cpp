#include "Camera.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;


Camera::Camera()
{
	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
}


Camera::~Camera()
{
}

void Camera::SetPoition(glm::vec3 a_Postion, glm::vec3 a_target)
{
	m_Postion = a_Postion;

	m_viewMatrix = glm::lookAt(
		m_Postion,
		a_target,
		m_up);
}

void Camera::Update(float deltaTime)
{
	const float speed = m_speed * deltaTime;
	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	// move the camera ford this is a test
	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		m_Postion += m_Front * speed;
	}
	// move the camera back
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		m_Postion -= m_Front * speed;
	}
	// move the camera up
	if (input->isKeyDown(aie::INPUT_KEY_Q))
	{
		m_Postion += m_up * speed;
	}
	// move the camera down
	if (input->isKeyDown(aie::INPUT_KEY_E))
	{
		m_Postion -= m_up * speed;
	}
	// move the camera left
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		glm::vec3 dir = glm::normalize(glm::cross(m_Front, m_up));
		m_Postion -= dir * speed;
	}
	// move the camera right
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		glm::vec3 dir = glm::normalize(glm::cross(m_Front, m_up));
		m_Postion += dir * speed;
	}

	if (/*input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT) ||*/ input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		const float mouseSensitivity = 100.0f * deltaTime;

		int mouseX, mouseY;
		float xOffset, yOffset;
		aie::Input *input = aie::Input::getInstance();
		input->getMouseXY(&mouseX, &mouseY);

		// get the change in the mouse movement.
		xOffset = (mouseX - m_lastMouseXPos) * mouseSensitivity;
		yOffset = (mouseY - m_lastMouseYPos) * mouseSensitivity;

		// adjust yaw and pitch based on movement
		m_Yaw += xOffset;
		m_Pitch += yOffset;

		if (m_Pitch > 89.0f) m_Pitch = 89.0f;
		if (m_Pitch < -89.0f) m_Pitch = -89.0f;

		glm::vec3 front;
		front.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		front.y = glm::sin(glm::radians(m_Pitch));
		front.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
	}

	m_viewMatrix = glm::lookAt(
		m_Postion,
		m_Postion + m_Front,
		m_up);

	input->getMouseXY(&m_lastMouseXPos, &m_lastMouseYPos);
}