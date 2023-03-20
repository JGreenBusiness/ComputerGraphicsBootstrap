#pragma once
#include <glm/glm.hpp>
class SimpleCamera
{
public:
	SimpleCamera();
	~SimpleCamera();

	glm::vec3 GetPosition()
		{ return m_position; }

	glm::mat4 GetWorldTransform(glm::vec3 position, glm::vec3
		eularAngles, glm::vec3 scale);

	glm::mat4 GetProjectionMatrix(float width, float height);
	glm::mat4 GetProjectionViewMatrix();
	glm::mat4 GetViewMatrix();

	float GetAspectRatio() { return m_aspectRatio; }

	void SetPosition(glm::vec3 pos) { pos = m_position; };
	void SetAspectRatio(float width, float height) 
		{ m_aspectRatio = width / height; }
	void SetViewMatrix(glm::vec3 from, glm::vec3 to,  )



protected:
	glm::mat4	m_projectionViewTransform;
	glm::mat4	m_worldTransoform;
	
	glm::vec3	m_position;

	float		m_aspectRatio;

	float		m_theta;
	float		m_phi;




private:
};

