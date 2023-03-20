#include "SimpleCamera.h"
#include <glm/ext.hpp>
#include <Input.h>

SimpleCamera::SimpleCamera()
{
	m_position = glm::vec3(-10, 2, 0);

	m_projectionViewTransform = glm::mat4();
	m_worldTransoform = glm::mat4();

	m_aspectRatio = 16.0f / 9.0f;

	m_phi = 0;
	m_theta = 0;
}

SimpleCamera::~SimpleCamera()
{
}



glm::mat4 SimpleCamera::GetViewMatrix()
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
		glm::cos(phiR)*glm::sin(thetaR));

	return glm::lookAt(m_position,m_position + forward, glm::vec3(0,1,0));
}

glm::mat4 SimpleCamera::GetProjectionMatrix(float width, float height)
{
	return glm::perspective(glm::pi<float>() * 0.25f, width / height,
		0.1f, 10000.f);
}

glm::mat4 SimpleCamera::GetWorldTransform(glm::vec3 position, glm::vec3 eularAngles, glm::vec3 scale)
{
	return glm::mat4();
}
