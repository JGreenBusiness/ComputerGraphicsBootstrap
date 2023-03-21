#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <list>

class SimpleCamera;
class Instance;

struct Light
{
	Light() 
	{
		direction = glm::vec3(0);
		colour = glm::vec3(1);
	}
	Light(glm::vec3 _position, glm::vec3 _colour, float _intensity)
	{
		direction = _position;
		colour = _colour * _intensity;
	}

	glm::vec3 direction;
	glm::vec3 colour;


};

class Scene
{
public:
	Scene(SimpleCamera* camera, glm::vec2 windowSize,
		Light& light, glm::vec3 ambientLightColour);
	~Scene() {};

	void AddInstance(Instance* instance);

	void Draw();

	SimpleCamera* GetCamera() { return m_camera; }
	glm::vec2 GetWindowSize() { return m_windowSize; }
	glm::vec3 GetAmbienColourLight() { return m_ambientLightColour; }
	Light GetLight() { return m_light; }

protected:
	SimpleCamera* m_camera;
	glm::vec2 m_windowSize;
	Light m_light;
	glm::vec3 m_ambientLightColour;
	std::list<Instance*> m_instances;


private:
};

