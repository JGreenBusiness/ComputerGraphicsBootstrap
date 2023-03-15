#include "SolarSystem.h"
#include "Gizmos.h"
#include "Input.h"


using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

SolarSystem::SolarSystem() {

}

SolarSystem::~SolarSystem() {

}

bool SolarSystem::startup() {

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(15), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	const int PLANET_NUM = 8;
	float planetSizes [PLANET_NUM] =
	{
		.2f,	//	Mercury
		.32f,	//	Venus
		.3f,	//	Earth
		.25f,	//	Mars
		.7f,	//	Jupiter
		.6f,	//	Saturn
		.4f,	//	Uranus
		.3f		//	Neptune
	};

	float distFromSun[PLANET_NUM] =
	{
		1.4f,	//	Mercury
		2.5f,	//	Venus
		3,		//	Earth
		3.5,		//	Mars
		4.8,		//	Jupiter
		5.1,		//	Saturn
		6,		//	Uranus
		6.9		//	Neptune
	};
	
	

	glm::vec4 planetColours [PLANET_NUM] =
	{
		glm::vec4(1, 0.93f, 0.73f,1),	//	Mercury
		glm::vec4(1, 0.78f, 0.19f,1),	//	Venus
		glm::vec4(0.35f, 0.46f, 1,1),	//	Earth
		glm::vec4(1, 0.98f, 0.83f,1),	//	Mars
		glm::vec4(1, 0.87f, 0.49f,1),	//	Jupiter
		glm::vec4(0.96f, 0.99f, 0.74f,1),	//	Saturn
		glm::vec4(0.68f, 0.89f, 0.89f,1),	//	Uranus
		glm::vec4(0.34f, 0.6f, 1,1)	//	Neptune
	};

	for (int i = 0; i < PLANET_NUM; i++)
	{
		m_planets.push_back(new Planetoid(glm::vec3(0), distFromSun[i], planetSizes[i], planetColours[i]));
	}

	return true;
}

void SolarSystem::shutdown() {

	Gizmos::destroy();
}

void SolarSystem::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	Gizmos::addSphere(glm::vec3(0), 1, 15, 15, glm::vec4(1, 0, 0, 0.5f));

	float planetSpeed[8] =
	{
		.4f,	//	Mercury
		.5f,	//	Venus
		.1f,	//	Earth
		.5f,	//	Mars
		.8f,	//	Jupiter
		.1f,	//	Saturn
		.2f,	//	Uranus
		.9f		//	Neptune
	};

	for (int i = 0; i < 8; i++)
	{
		m_planets[i]->DrawOrbitingPlanet(getTime()*planetSpeed[i], 1.5f, glm::vec3(0, 1, 0));
	}
	

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void SolarSystem::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}

