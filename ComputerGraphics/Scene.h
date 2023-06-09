#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <list>

class SimpleCamera;
class Instance;

const int MAX_LIGHTS = 4;

struct Light
{
	Light() 
	{
		position = glm::vec3(0);
		colour = glm::vec3(1);
	}
	Light(glm::vec3 _position, glm::vec3 _colour, float _intensity)
	{
		position = _position;
		colour = _colour * _intensity;
	}

	glm::vec3 position;
	glm::vec3 colour;


};

class Scene
{
public:
	Scene(SimpleCamera* camera, glm::vec2 windowSize,
		Light& light, glm::vec3 ambientLightColour);
	~Scene();

	/// <summary> Adds an instance to the scene</summary>
	void AddInstance(Instance* instance);

	void Draw();

	void AddPointLights(Light light) 
	{
		m_pointLights.push_back(light);
	}
	void AddPointLights(glm::vec3 position, glm::vec3 colour, float intensity)
		{m_pointLights.push_back(Light(position,colour, intensity));}

	void SetPointLight(int _index, Light _pointLight) { m_pointLights[_index] = _pointLight; }

	SimpleCamera* GetCamera() { return m_camera; }
	glm::vec2 GetWindowSize() { return m_windowSize; }
	glm::vec3 GetAmbienColourLight() { return m_ambientLightColour; }
	Light GetLight() { return m_light; }
	std::vector<Light> GetLights() { return m_pointLights; }
	int GetNumberOfLights() { return m_pointLights.size(); }

	/// <summary> Returns read only positions of point lights</summary>
	glm::vec3* GetPointLightPositions() { return &m_pointLightPositions[0];}

	/// <summary> Returns read only colours of point lights</summary>
	glm::vec3* GetPointLightColours() { return &m_pointLightColours[0];}

	std::vector<Light> GetPointLights() { return m_pointLights; }

	void SetCamera(SimpleCamera* camera) { m_camera = camera; }

protected:
	SimpleCamera* m_camera;
	glm::vec2 m_windowSize;

	Light m_sunLight;
	std::vector<Light> m_pointLights;

	Light m_light;
	glm::vec3 m_ambientLightColour;
	std::list<Instance*> m_instances;

	glm::vec3 m_pointLightPositions[MAX_LIGHTS];
	glm::vec3 m_pointLightColours[MAX_LIGHTS];


private:
};

