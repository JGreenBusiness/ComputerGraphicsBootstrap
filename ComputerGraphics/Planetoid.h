#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Gizmos.h"

class Planetoid
{
public:
	Planetoid(glm::vec3 _pos,float _dist, float _radius, glm::vec4 _colour);
	~Planetoid();

	void Update(float _dt);
	void Draw();

	void SetTransform(glm::mat4* _mat) { m_transform = _mat; }
	glm::mat4* GetTransform() { return m_transform; }
	float GetRadius() { return m_radius; }

	void DrawOrbitingPlanet(float _time, float _speed, const glm::vec3& _axis);
	glm::mat4 RotAroundPoint(float rad, const glm::vec3& point, const glm::vec3& axis);

protected:
	float m_radius;
	float m_distFromSun;
	glm::vec3 m_origin;
	glm::mat4* m_transform;
	glm::vec4 m_colour;

};