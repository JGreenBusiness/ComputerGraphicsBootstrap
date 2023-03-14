#include "Planetoid.h"
#include "Gizmos.h"

Planetoid::Planetoid(glm::vec3 _pos, float _radius)
{
	m_origin = _pos;
	m_radius = _radius;
	m_transform = new glm::mat4(1);
}

Planetoid::~Planetoid()
{
	delete m_transform;
}

void Planetoid::Update(float _dt)
{
	
}

void Planetoid::Draw()
{
	aie::Gizmos::addSphere(m_origin, m_radius, 15, 15, glm::vec4(1, 0, 0, 0.5f),&*m_transform);
	m_transform = new glm::mat4(1);
}

void Planetoid::RotatePlanetAround(float _time,float _speed)
{
	*m_transform = glm::translate(*m_transform, glm::vec3(glm::sin(_time * _speed), 0, glm::cos(_time * _speed)));
}
