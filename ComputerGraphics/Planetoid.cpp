#include "Planetoid.h"
#include "Gizmos.h"

Planetoid::Planetoid(glm::vec3 _pos, float _radius, glm::vec4 _colour)
{
	m_origin = _pos;
	m_radius = _radius;
	m_transform = new glm::mat4(1);
	m_colour = _colour;
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
	aie::Gizmos::addSphere(m_origin, m_radius, 15, 15, m_colour,&*m_transform);
	m_transform = new glm::mat4(1);
}

void Planetoid::RotatePlanetAround(float _time,float _speed, float _dist)
{
	glm::mat4 mat = glm::mat4(_dist);

	//mat[0] = glm::vec4(1,0,0,0);
	//mat[1] = glm::vec4(0,1,0,0);
	//mat[2] = glm::vec4(0,0,1,0);
	//mat[3] = glm::vec4(0,0,0,1);

	*m_transform = glm::translate(*m_transform * mat, glm::vec3(glm::sin(_time * _speed), 0, glm::cos(_time * _speed)));
}
