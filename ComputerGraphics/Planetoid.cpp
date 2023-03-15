#include "Planetoid.h"
#include "Gizmos.h"

Planetoid::Planetoid(glm::vec3 _pos,float _dist, float _radius, glm::vec4 _colour)
{
	m_origin = _pos;
	m_radius = _radius;
	m_colour = _colour;
	m_distFromSun = _dist;

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
	
}

void Planetoid::DrawOrbitingPlanet(float _time, float _speed, const glm::vec3& _axis)
{
	glm::mat4 mat = *m_transform;

	//mat[0] = glm::vec4(1,0,0,0);
	//mat[1] = glm::vec4(0,1,0,0);
	//mat[2] = glm::vec4(0,0,1,0);
	//mat[3] = glm::vec4(0,0,0,1);

	//*m_transform = glm::translate(*m_transform * mat, glm::vec3(glm::sin(_time * _speed), 0, glm::cos(_time * _speed)));

	

	mat = RotAroundPoint(_time * _speed, glm::vec3(m_distFromSun,0,0), _axis);
	*m_transform = mat;

	//m_origin -= glm::vec3(m_distFromSun, 0, 0);
	aie::Gizmos::addSphere(m_origin, m_radius, 15, 15, m_colour, &*m_transform);
	//m_origin += glm::vec3(m_distFromSun, 0, 0);

}

glm::mat4 Planetoid::RotAroundPoint(float rad, const glm::vec3& point, const glm::vec3& axis)
{
	glm::mat4 t1 = glm::translate(glm::mat4(1), -point);
	glm::mat4 r = glm::rotate(glm::mat4(1), rad, axis);
	glm::mat4 t2 = glm::translate(glm::mat4(1), point);
	return t2 * r * t1;
}
