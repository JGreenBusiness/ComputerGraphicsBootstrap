#pragma once
#include "Application.h"
#include "glm/glm.hpp"
#include <glm/ext.hpp>
#include "Planetoid.h"
#include <vector>
#include "FlyCamera.h"

class SolarSystem : public aie::Application
{
public:

	SolarSystem();
	virtual ~SolarSystem();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	const glm::mat4* m_mat;

	std::vector<Planetoid*> m_planets;

	FlyCamera	m_camera;


};

