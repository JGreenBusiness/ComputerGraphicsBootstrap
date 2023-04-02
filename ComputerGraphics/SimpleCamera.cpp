#include "SimpleCamera.h"
#include <Input.h>

SimpleCamera::SimpleCamera()
{
	m_worldTransoform = glm::mat4(1);
	m_viewMatrix = glm::mat4(1);
	m_projectionMatrix = glm::mat4(1);
	m_projectionViewMatrix = glm::mat4(1);

	m_eularOrientation = glm::vec3(0);

	m_aspectRatio = 16.0f / 9.0f;
}

SimpleCamera::~SimpleCamera()
{
}

void SimpleCamera::Update(float deltaTime)
{
}


void SimpleCamera::SetRotation(glm::vec3 eularAngles)
{
	SetWorldTransform(GetPosition(), eularAngles, glm::vec3(1));
}

glm::mat4 SimpleCamera::SetWorldTransform(glm::vec3 position, glm::vec3 eularAngles, glm::vec3 scale)
{
	m_eularOrientation = eularAngles;
	return m_worldTransoform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1),
			glm::radians(eularAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1),
			glm::radians(eularAngles.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1),
			glm::radians(eularAngles.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void SimpleCamera::SetViewMatrix(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	m_viewMatrix = glm::lookAt(from, to, up);
}

glm::mat4 SimpleCamera::SetViewMatrix()
{
	return m_viewMatrix = glm::lookAt(glm::vec3(0, 0, 0),glm::vec3(1,0,0), glm::vec3(0, 1, 0)) / m_worldTransoform;
}

void SimpleCamera::SetProjectionMatrix(float fieldOfView, float aspectRatio, float near, float far)
{
	m_projectionMatrix = glm::perspective(fieldOfView, aspectRatio, near, far);
}



