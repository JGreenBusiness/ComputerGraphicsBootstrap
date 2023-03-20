#include "SimpleCamera.h"
#include <glm/ext.hpp>
#include <Input.h>

SimpleCamera::SimpleCamera()
{
	m_position = glm::vec3(-10, 2, 0);

	m_projectionViewTransform = glm::mat4();
	m_worldTransoform = glm::mat4();
	m_viewTransoform = glm::mat4();

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

glm::mat4 SimpleCamera::GetProjectionViewMatrix(float width, float height)
{
	return GetProjectionMatrix(width, height) * GetViewMatrix();
}
glm::mat4 SimpleCamera::GetProjectionMatrix(float width, float height)
{
	return glm::perspective(glm::pi<float>() * 0.25f, width / height,
		0.1f, 10000.f);
}

glm::mat4 SimpleCamera::GetWorldTransform(glm::vec3 position, glm::vec3 eularAngles, glm::vec3 scale)
{
	glm::mat4 mat;
	mat[0] = glm::vec4(		scale.x		, 0			, 0				,0);
	mat[1] = glm::vec4(		0			, scale.y	, 0				,0);
	mat[2] = glm::vec4(		0			, 0			, scale.z		,0);
	mat[3] = glm::vec4(		position.x	, position.y, position.z	,1);

	mat = glm::rotate(mat, glm::radians(eularAngles.x), glm::vec3(1, 0, 0));
	mat = glm::rotate(mat, glm::radians(eularAngles.y), glm::vec3(0, 1, 0));
	mat = glm::rotate(mat, glm::radians(eularAngles.z), glm::vec3(0, 0, 1));
	return mat;
}

void SimpleCamera::SetViewMatrix(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
		glm::cos(phiR) * glm::sin(thetaR));

	m_viewTransoform = glm::lookAt(from, to, up);
}

void SimpleCamera::SetProjectionMatrix(float fieldOfView, float aspectRatio, float near, float far)
{
	glm::mat4 projMat = glm::perspective(fieldOfView, aspectRatio,near,far);
	
	m_projectionViewTransform = projMat * m_viewTransoform;
}

void SimpleCamera::SetProjectionMatrix(float fieldOfView, float width, float height, float near, float far)
{
	glm::mat4 projMat = glm::perspective(fieldOfView, width/height, near, far);

	m_projectionViewTransform = projMat * m_viewTransoform;
}

