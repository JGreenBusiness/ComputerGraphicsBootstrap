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

	m_shapeRot = 0;
	m_shapeRotAxis = glm::vec3(0,1,0);

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
	//QuadDraw(pv * m_quadTransform);
		
	//Draw the bunny up in BunnyLoader
	//BunnyDraw(pv * m_bunnyTransform);

	//PhongDraw(pv * m_bunnyTransform,m_bunnyTransform);


	glm::mat4& currentShape = m_diskTransform;
	if(m_shapeRotAxis != glm::vec3(0))
	{
		currentShape = glm::rotate(currentShape,glm::radians(m_shapeRot),m_shapeRotAxis);
	}
	// Draws the Box setup in BoxLoader
	//SimpleDraw(pv * m_boxTransform, m_boxMesh);
	
	// Draws the Box setup in BoxLoader
	SimpleDraw(pv * m_diskTransform, m_diskMesh);
	
	// Draws the Box setup in BoxLoader
	//SimpleDraw(pv * m_pyramidTransform, m_pyramidMesh);


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

	if (!BoxLoader())
	{
		return false;
	}

	if (!DiskLoader())
	{
		return false;
	}

	if (!PyramidLoader())
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
	
ImGui::Begin("Box Rot Settings");
	ImGui::DragFloat3("Box Rot Axis", 
		&m_shapeRotAxis[0],0.1f,0,1);
	ImGui::DragFloat("Box Rot",
		&m_shapeRot,0.01f, -1.0f,1);
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

	vertices[0].position = { -.5f,	0,	0.5f,	1 };
	vertices[1].position = { 0.5f,	0,	0.5f,	1 };
	vertices[2].position = { -.5f,	0,	-.5f,	1 };
	vertices[3].position = { 0.5f,	0,	-.5f,	1 };

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


bool ComputerGraphicsApp::BoxLoader()
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

	// Defined as 4 vertices for the 2 triangles
	Mesh::Vertex vertices[8];

	vertices[0].position = { -.5f,	0,	0.5f,	1 };
	vertices[1].position = { 0.5f,	0,	0.5f,	1 };
	vertices[2].position = { -.5f,	0,	-.5f,	1 };
	vertices[3].position = { 0.5f,	0,	-.5f,	1 };
	
	vertices[4].position = { 0.5f,	1,	-.5f,	1 };
	vertices[5].position = { 0.5f,	1,	0.5f,	1 };
	vertices[6].position = { -.5f,	1,	0.5f,	1 };
	vertices[7].position = { -.5f,	1,	-.5f,	1 };

	vertices[0].normal = {0,1,0,0};
	vertices[1].normal = {0,1,0,0};
	vertices[2].normal = {0,1,0,0};
	vertices[3].normal = {0,1,0,0};
	vertices[4].normal = {0,1,0,0};
	vertices[5].normal = {0,1,0,0};
	vertices[6].normal = {0,1,0,0};
	vertices[7].normal = {0,1,0,0};

	unsigned int indices[36] =
		{
		1,0,2,2,3,1,	// Facing -Y
		3,4,5,3,5,1,	// Facing +X
		6,0,1,1,5,6,	// Facing -Z
		6,5,7,7,5,4,	// Facing +Y
		4,3,2,4,2,7,	// Facing -X
		7,2,6,2,0,6		// Facing +Z
		};

	m_boxMesh.Initialise(8, vertices, 36, indices);

	// This is a 10 'unit' wide quad
	m_boxTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1
	};

	return true;
}

bool ComputerGraphicsApp::DiskLoader()
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

	// Positions of a circle not including the centre
	std::vector<glm::vec4> vertPositions = CreateCircleArray(.5f,glm::vec3(0),30);

	// The verticies will be the fragment amount of the circle plus one to include the centre
	Mesh::Vertex vertices[31];

	// Setting the centre vert pos 
	vertices[0].position = glm::vec4(0,0,0,1);

	// Setting the vert pos for all points around the circle
	for(int i = 1;i < 31; i++)
	{
		vertices[i].position = vertPositions[i];
	}

	// index count is fragment amount * 3
	const int indexCount = 90;
	unsigned int indices[indexCount];
	int indexOffset = 0;

	// The draw order starts at 0 and index then counts up,
	// every 3rd number will also be 0, then the number before 3rd will repeat.
	// When the last number is reached, to complete the circle the draw order must finish at 1
	// e.g. If there were 12 segements indices would be:
	//		0,1,2,0,2,3,0,3,4,0...10,11,0,11,12,1 
	indices[0] = 0;
	for (int i = 1; i < indexCount; i++)
	{
		if (i == indexCount-1)
		{
			indices[i] = 1;
		}
		else if (i % 3 == 0)
		{
			indices[i] = 0;
			indexOffset+=2;
		}
		else
		{
			indices[i] = i - indexOffset;
		}
	}


	m_diskMesh.Initialise(31, vertices, indexCount, indices);

	// This is a 10 'unit' wide quad
	m_diskTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1
	};

	return true;
}

std::vector<glm::vec4> ComputerGraphicsApp::CreateCircleArray(float radius, glm::vec3 pos, int fragments)
{
	const float PI = 3.1415926f;

	std::vector<glm::vec4> circlePoints;

	float increment = 2.0f * PI / fragments;

	for (float currentAngle = 0.0f; currentAngle <= 2.0f * PI; currentAngle += increment)
	{
		circlePoints.push_back(glm::vec4(radius * cos(currentAngle) + pos.x, radius * sin(currentAngle) + pos.y, pos.z,1));
	}

	return circlePoints;
}

bool ComputerGraphicsApp::PyramidLoader()
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

	vertices[0].position = { 0.0f,	0,	0.55f,	1 };
	vertices[1].position = { -.5f,	0,	-.5f,	1 };
	vertices[2].position = { 0.5f,	0,	-.5f,	1 };
	vertices[3].position = { 0.0f,	1,	0.0f,	1 };

	unsigned int indices[12] =
	{
		0,1,2,
		1,3,2,
		2,3,0,
		0,3,1


	};

	m_pyramidMesh.Initialise(4, vertices, 12, indices);

	// This is a 10 'unit' wide quad
	m_pyramidTransform =
	{
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1
	};

	return true;
}

void ComputerGraphicsApp::SimpleDraw(glm::mat4 pvm, Mesh& mesh)
{
	// Bind the Shader
	m_simpleShader.bind();

	//Bind the transform
	m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	// Draw the quad using mesh's draw
	mesh.Draw();
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

void ComputerGraphicsApp::PhongDraw(glm::mat4 pvm, glm::mat4 transform, Mesh& mesh)
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

	mesh.Draw();
}
