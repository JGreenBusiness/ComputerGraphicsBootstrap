#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
class SimpleCamera
{
public:
	SimpleCamera();
	~SimpleCamera();

	virtual void Update(float deltaTime);

	// Getters
	glm::vec3 GetPosition(){ return (glm::vec3)m_worldTransoform[3]; }

	/// <summary> Returns eular angle orientation </summary>
	glm::vec3 GetEular() { return m_eularOrientation; };
	glm::mat4 GetWorldTransform() { return m_worldTransoform; };
	glm::mat4 GetProjectionMatrix() { return m_projectionMatrix; }
	glm::mat4 GetViewMatrix() { return m_viewMatrix; };
	glm::mat4 GetProjectionViewMatrix() { return m_projectionViewMatrix; };
	float GetAspectRatio() { return m_aspectRatio; }

	// Setters
	
	/// <summary> Translates Camera's world transform</summary>
	void Translate(glm::vec3 pos) { m_worldTransoform = glm::translate(m_worldTransoform,pos); }
	
	/// <summary> Sets rotation using eular angles.</summary>
	void SetRotation(glm::vec3 eularAngles);
	void SetAspectRatio(float width, float height) { m_aspectRatio = width / height; }
	void SetWorldTransform(glm::mat4 _transform) {m_worldTransoform = _transform;}
	glm::mat4 SetWorldTransform(glm::vec3 position, glm::vec3 eularAngles, glm::vec3 scale);
	void SetViewMatrix(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	virtual glm::mat4 SetViewMatrix();
	void SetProjectionMatrix(float feildOfView, float aspectRatio,float near, float far);


protected:
	glm::mat4	m_worldTransoform;
	glm::vec3	m_eularOrientation;

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
	glm::mat4	m_projectionViewMatrix;
		
	float		m_aspectRatio;





private:
};

