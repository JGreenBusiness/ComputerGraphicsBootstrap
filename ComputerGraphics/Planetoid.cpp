#include "Planetoid.h"
#include "Gizmos.h"

Planetoid::Planetoid(glm::vec3 _pos, float _radius)
{
	m_origin = _pos;

}

Planetoid::~Planetoid()
{

}

void Planetoid::Update(float _dt)
{
	
}

void Planetoid::Draw()
{
	aie::Gizmos::addSphere(glm::vec3(0), m_size, 15, 15, glm::vec4(1, 0, 0, 0.5f),&*transform);
}