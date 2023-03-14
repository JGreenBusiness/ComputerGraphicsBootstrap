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

	//aie::Gizmos::addSphere(glm::vec3(0), 1, 15, 15, glm::vec4(1, 0, 0, 0.5f));


	//glm::mat4 mercury = glm::mat4(1);

	//float time = aie::getTime();
	//mercury = glm::translate(mercury, glm::vec3(glm::sin(time * 1.0f), 0, glm::cos(time * 1.0f)));

	//aie::Gizmos::addSphere(glm::vec3(0), .5, 12, 12, glm::vec4(1), &mercury);
}

void Planetoid::Draw()
{
	aie::Gizmos::addSphere(glm::vec3(0), m_size, 15, 15, glm::vec4(1, 0, 0, 0.5f),&*transform);
}