#include "Scene.h"
#include "Instance.h"

Scene::Scene(SimpleCamera* camera, glm::vec2 windowSize,
	Light& light, glm::vec3 ambientLightColour) :
	m_camera(camera), m_windowSize(windowSize), m_light(light),
	m_ambientLightColour(ambientLightColour)
{

}

Scene::~Scene()
{
	// Deconstructs all instences in scene
	for (auto it = m_instances.begin();
		it != m_instances.end(); it++)
	{
		delete *it;
		*it = nullptr;
	}
}

void Scene::AddInstance(Instance* instance)
{
	m_instances.push_back(instance);
}

void Scene::Draw()
{
	// Sets getter variables for point lights
	for (int i = 0; i < MAX_LIGHTS && i < m_pointLights.size(); i++)
	{
		m_pointLightPositions[i] = m_pointLights[i].position;
		m_pointLightColours[i] = m_pointLights[i].colour;
	}

	// Draws all intances
	for (auto it = m_instances.begin();
		it != m_instances.end(); it++)
	{
		Instance* instance = *it;
		instance->Draw(this);
	}
}
