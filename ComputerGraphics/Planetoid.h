#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Gizmos.h"

class Planetoid
{
public:
	Planetoid(glm::vec3 _pos, float _radius);
	~Planetoid();

	void Update(float _dt);
	void Draw();

	void SetTransform(glm::mat4* _mat) { transform = _mat; };
	glm::mat4* GetTransform() { return transform; }

protected:
	float m_size;
	glm::vec3 m_origin;
	glm::mat4* transform;
};