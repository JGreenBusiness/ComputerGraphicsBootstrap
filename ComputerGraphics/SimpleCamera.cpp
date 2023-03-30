#include "SimpleCamera.h"
#include <Input.h>

SimpleCamera::SimpleCamera()
{
	m_worldTransoform = glm::mat4(1);
	m_viewMatrix = glm::mat4(1);
	m_projectionMatrix = glm::mat4(1);
	m_projectionViewMatrix = glm::mat4(1);

	m_aspectRatio = 16.0f / 9.0f;
}

SimpleCamera::~SimpleCamera()
{
}

void SimpleCamera::Update(float deltaTime)
{
}

glm::mat4 SimpleCamera::SetWorldTransform(glm::vec3 position, glm::vec3 eularAngles, glm::vec3 scale)
{
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
	glm::vec3 pos = m_worldTransoform[3];

	float x = atan2(-m_worldTransoform[1][2], m_worldTransoform[2][2]);
	float cosY = sqrt(1 - m_worldTransoform[0][2]);
	float y = atan2(m_worldTransoform[0][2], cosY);

	float thetaR = x;
	float phiR = y;
	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),glm::cos(phiR) * glm::sin(thetaR));

	return m_viewMatrix = glm::lookAt(pos, pos + glm::vec3(1,0,0), glm::vec3(0, 1, 0)) ;
}

void SimpleCamera::SetProjectionMatrix(float fieldOfView, float aspectRatio, float near, float far)
{
	m_projectionMatrix = glm::perspective(fieldOfView, aspectRatio, near, far);
}

