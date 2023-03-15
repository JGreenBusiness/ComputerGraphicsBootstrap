#include "ComputerGraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include "imgui.h"


using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

ComputerGraphicsApp::ComputerGraphicsApp() {

}

ComputerGraphicsApp::~ComputerGraphicsApp() {

}

bool ComputerGraphicsApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(15), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	m_light.colour = { 1,1,0 };
	m_ambientLight = { .5f,.5f,.5f };

	return LaunchShaders();
}

void ComputerGraphicsApp::shutdown() {

	Gizmos::destroy();
}

void ComputerGraphicsApp::update(float deltaTime) {

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


	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	// Grab the time since the application has started
	float time = getTime();

	// Rotate the light to emulate a 'day/night' cycle
	m_light.direction = 
		glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2),0));

	


	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	
	ImGUIRefresher();
}

void ComputerGraphicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	auto pv = m_projectionMatrix * m_viewMatrix ;
	// Draws he quad setup in QuadLoader
	QuadDraw(pv * m_quadTransform);

	//Draw the bunny up in BunnyLoader
	//BunnyDraw(pv * m_bunnyTransform);

	PhongDraw(pv * m_bunnyTransform,m_bunnyTransform);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}

bool ComputerGraphicsApp::LaunchShaders()
{
	// used for loading in a simple quad
	if (!QuadLoader())
	{
		return false;
	}

	// used for loading in an OBJ bunny
	if (!BunnyLoader())
	{
		return false;
	}


	return true;
}

void ComputerGraphicsApp::ImGUIRefresher()
{
	ImGui::Begin("Light Settings");
	ImGui::DragFloat3("Global Light Colour", 
		&m_light.colour[0],0.1f,0,1);
	ImGui::DragFloat3("Glabal Light Direction",
		&m_light.direction[0],0.1f, 01,1);
	ImGui::End();
;}

bool ComputerGraphicsApp::QuadLoader()
{
	m_simpleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (m_simpleShader.link() == false)
	{
		printf("Simple Shader has an Error: %s\n", m_simpleShader.getLastError());
		return false;
	}

	// Defined as 4 vertices for the 2 triangles
	Mesh::Vertex vertices[4];

	vertices[0].position = { -.5f,0, .5f,1 };
	vertices[1].position = { .5f,0, .5f,1 };
	vertices[2].position = { -.5f,0,-.5f,1 };
	vertices[3].position = { .5f,0,-.5f,1 };

	unsigned int indices[6] = { 0,1,2,2,1,3 };




	m_quadMesh.Initialise(4, vertices, 6, indices);

	// This is a 10 'unit' wide quad
	m_quadTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1
	};

	return true;
}

void ComputerGraphicsApp::QuadDraw(glm::mat4 pvm)
{
	// Bind the Shader
	m_simpleShader.bind();

	//Bind the transform
	m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	// Draw the quad using mesh's draw
	m_quadMesh.Draw();
}

bool ComputerGraphicsApp::BunnyLoader()
{
	m_phongShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/Phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/Phong.frag");
	if (m_phongShader.link() == false)
	{
		printf("Color shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}
	if (m_bunnyMesh.load("./stanford/Bunny.obj") == false)
	{
		printf("Bunny Mesh Error!\n");
		return false;
	}
	m_bunnyTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	
	return true;
}

void ComputerGraphicsApp::BunnyDraw(glm::mat4 pvm)
{
	// Bind the shader   
	m_colourShader.bind();
	// Bind the transform    
	m_colourShader.bindUniform("ProjectionViewModel", pvm);
	// Bind the color     
	m_colourShader.bindUniform("BaseColour", glm::vec4(1));
	m_bunnyMesh.draw();
}

void ComputerGraphicsApp::PhongDraw(glm::mat4 pvm, glm::mat4 transform)
{
	// Bind the phong shader
	m_phongShader.bind();

	// Bind the camera position
	m_phongShader.bindUniform("CameraPosition",
		glm::vec3(glm::inverse(m_viewMatrix)[3]));

	//Bind the direction light we defind
	m_phongShader.bindUniform("LightDirection", m_light.direction);
	m_phongShader.bindUniform("AmbientColour", m_ambientLight);
	m_phongShader.bindUniform("LightColour", m_light.colour);

	// bind the pvm using the one provided
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// bind the transofrm using the one provided
	m_phongShader.bindUniform("ModelMatrix", transform);

	m_bunnyMesh.draw();
}
