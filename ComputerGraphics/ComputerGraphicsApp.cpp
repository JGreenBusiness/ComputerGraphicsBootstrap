#include "ComputerGraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include "imgui.h"
#include <iostream>

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


	m_flyCamera = new FlyCamera();
	m_stillCamera = new StationaryCamera();
	m_enableFlyCam = false;
	m_camera = m_stillCamera;

	m_camPos = glm::vec3(-20, 5, 0);
	m_camRot = glm::vec3(0);
	m_flyCamera->SetPosition(m_camPos);
	m_stillCamera->SetPosition(m_camPos);


	// create simple camera transforms
	m_flyCamera->SetProjectionMatrix(45,getWindowWidth()/getWindowHeight(),0.1f,10000.f);
	m_stillCamera->SetProjectionMatrix(45,getWindowWidth()/getWindowHeight(),0.1f,10000.f);
	m_projectionMatrix = m_camera->GetProjectionMatrix();
	m_viewMatrix = m_camera->GetViewMatrix();


	m_mainLight = new Light(glm::vec3(1,-1,1),glm::vec3(0),1);

	m_ambientLight = { .5f,.5f,.5f };

	m_emitter = new ParticleEmitter();
	m_emitter->Initialise(5000, 500, 0.1f, 1.0f,
		1.0f, 5, 1, 0.1f,
		glm::vec4(1,0,0,1), glm::vec4(1, 1, 0, 1));

	m_scene = new Scene(m_camera, glm::vec2(getWindowWidth(), getWindowHeight()),
		*m_mainLight, m_ambientLight);

	m_pointLight1 = new Light(glm::vec3(5, 10, 0), glm::vec3(1, 0, 0), 20);
	m_pointLight2 = new Light(glm::vec3(8, 10, 0), glm::vec3(0, 0, 1), 20);
	m_scene->AddPointLights(*m_pointLight1);
	m_scene->AddPointLights(*m_pointLight2);

	m_shapeRot = 0;
	m_shapeRotAxis = glm::vec3(0,1,0);
	
	m_isTextured = 0;

	return LaunchShaders();
}

void ComputerGraphicsApp::shutdown() 
{
	if (m_camera != nullptr)
	{
		delete m_camera;
	}

	if (m_scene != nullptr)
	{
		delete m_scene;
	}
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
	m_scene->GetLight().direction =
		glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2),0));


	m_emitter->Update(deltaTime, m_camera->SetWorldTransform(m_camera->GetPosition(), glm::vec3(0), glm::vec3(1)));

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	
	ImGUIRefresher();
}

void ComputerGraphicsApp::draw()
{
	// Bind the render target as the first 
	// part of our draw function
	m_renderTarget.bind();


	// wipe the screen to the background colour
	clearScreen();

	m_viewMatrix = m_camera->SetViewMatrix();
	m_projectionMatrix = m_camera->GetProjectionMatrix();

	auto pv = m_projectionMatrix * m_viewMatrix ;

	m_scene->Draw();

	m_particleShader.bind();
	m_particleShader.bindUniform("ProjectionViewModel", pv * m_particlemitTransform);
	m_emitter->Draw();

	DrawGizmo(pv, m_boxTransform, m_boxMesh, m_flyCamera->GetPosition());
	DrawGizmo(pv, m_boxTransform, m_boxMesh, m_stillCamera->GetPosition());
	DrawGizmo(pv, m_boxTransform, m_boxMesh, m_pointLight1->direction);
	DrawGizmo(pv, m_boxTransform, m_boxMesh, m_pointLight2->direction);
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
	

	

	// Unbind the target to return to the backbuffer
	m_renderTarget.unbind();

	clearScreen();

	

	// Bind Post Processing Shader and the texture
	m_postProcessShader.bind();
	m_postProcessShader.bindUniform("colourTarget",0);
	m_postProcessShader.bindUniform("postProcessTarget", m_postProcessEffect);
	m_postProcessShader.bindUniform("windowWidth", (int) getWindowWidth());
	m_postProcessShader.bindUniform("windowHeight", (int) getWindowHeight());
	m_postProcessShader.bindUniform("time", getTime());

	m_renderTarget.getTarget(0).bind(0);


	m_fullScreenQuad.Draw();
	

	// Draws he quad setup in QuadLoader
	//TexturedQuadDraw(pv * m_texturedQuadTransform);


	// Draws he quad setup in QuadLoader
	//QuadDraw(pv * m_quadTransform);
		
	//Draw the bunny up in BunnyLoader
	//BunnyDraw(pv * m_bunnyTransform);

	//Draws the spear with light texture
	//OBJDraw(pv, m_spearTransform, m_spearMesh);


	//OBJDraw(pv, m_gunTransform, m_gunMesh);


	//PhongDraw(pv * m_spearTransform, m_spearTransform);


	//glm::mat4& currentShape = m_spearTransform;
	//if(m_shapeRotAxis != glm::vec3(0))
	//{
	//	currentShape = glm::rotate(currentShape,glm::radians(m_shapeRot),m_shapeRotAxis);
	//}
	// Draws the Box setup in BoxLoader
	//SimpleDraw(pv * m_boxTransform, m_boxMesh);
	
	// Draws the Disk setup in DiskLoader
	//SimpleDraw(pv * m_diskTransform, m_diskMesh);
		
	// Draws the Disk setup in DiskLoader
	//SimpleDraw(pv * m_coneTransform, m_coneMesh);
	
	// Draws the Pyramid setup in PyramidLoader
	//SimpleDraw(pv * m_pyramidTransform, m_pyramidMesh);

	

	//SpearDraw(pv * m_spearTransform);

	
}



bool ComputerGraphicsApp::LaunchShaders()
{
	if (m_renderTarget.initialise(1,getWindowWidth()
		,getWindowHeight()) == false)
	{
		printf("Render Target Error\n");
		return false;
	}

#pragma region LoadingShaders
	m_normalShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/normalLit.vert");
	m_normalShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/normalLit.frag");
	if (m_normalShader.link() == false)
	{
		printf("NormalLit shader Error: %s\n", m_normalShader.getLastError());
		return false;
	}


	// Post processing shader
	m_postProcessShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/post.vert");
	m_postProcessShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/post.frag");
	if (m_postProcessShader.link() == false)
	{
		printf("post shader Error: %s\n", m_postProcessShader.getLastError());
		return false;
	}

	// Partical Shader shader
	m_particleShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/particle.vert");
	m_particleShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/particle.frag");
	if (m_particleShader.link() == false)
	{
		printf("Particle Shader Error: %s\n", m_particleShader.getLastError());
		return false;
	}
#pragma endregion

	m_particlemitTransform =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	
	// used for loading in a simple quad
	//if (!QuadLoader())
	//{
	//	return false;
	//}

	//// used for loading in an OBJ bunny
	//if (!BunnyLoader())
	//{
	//	return false;
	//}

	if (!BoxLoader())
	{
		return false;
	}

	//if (!DiskLoader())
	//{
	//	return false;
	//}

	//if (!PyramidLoader())
	//{
	//	return false;
	//}
	//
	//if (!ConeLoader())
	//{
	//	return false;
	//}
	//	
	if (!TexturedQuadLoader())
	{
		return false;
	}

	// Create a full screen quad
	m_fullScreenQuad.InitialiseFullscreenQuad();
			
	if (!SpearLoader())
	{
		return false;
	}
			
	/*if (!GunLoader())
	{
		return false;
	}*/
	
	//if (!OBJLoader(m_spearMesh, m_spearTransform,1.0f,
	//	"./soulspear/", "soulspear.obj", false))
	//{
	//	return false;
	//}

	for (int i = 0; i < 10; i++)
	{
		m_scene->AddInstance(new Instance(glm::vec3(i*2,0,0),glm::vec3(0,i*30,0),
			glm::vec3(1,1,1), &m_spearMesh, &m_normalShader));
	}

	

	return true;
}

void ComputerGraphicsApp::ImGUIRefresher()
{
	ImGui::Begin("Light Settings");
	ImGui::DragFloat3("Global Light Colour", 
		&m_mainLight->colour[0], 0.1f, 0, 1);
	ImGui::DragFloat3("Glabal Light Direction",
		&m_mainLight->direction[0],0.1f, 01,1);
	ImGui::End();
	
ImGui::Begin("Box Rot Settings");
	ImGui::DragFloat3("Box Rot Axis", 
		&m_shapeRotAxis[0],0.1f,0,1);
	ImGui::DragFloat("Box Rot",
		&m_shapeRot,0.01f, -1.0f,1);
	ImGui::End();

ImGui::Begin("Post Processing Effect");
ImGui::InputInt("Post Effect Index",
	&m_postProcessEffect);
	ImGui::End();

	ImGui::Begin("Particle Effects");
	ImGui::DragFloat3("Patricle Position",
		&m_particlemitTransform[3][0], .1f, -100, 100);
	ImGui::End();


	ImGui::Begin("Camera Settings");
	ImGui::DragFloat3("Camera Pos",
		&m_camPos[0], .1f, -1000, 1000);
	ImGui::DragFloat3("Camera Rot",
		&m_camRot[0], 1.f, -1000, 1000);
	ImGui::Checkbox("EnableFlyCam",
		&m_enableFlyCam);
	ImGui::End();

	m_stillCamera->SetWorldTransform(m_camPos,m_camRot,glm::vec3(1));

	if (m_camera != m_flyCamera && m_enableFlyCam)
	{
		m_camera = m_flyCamera;
		m_scene->SetCamera(m_camera);
	}
	else if(m_camera != m_stillCamera && !m_enableFlyCam)
	{
		m_camera = m_stillCamera;
		m_scene->SetCamera(m_camera);
	}
	
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

bool ComputerGraphicsApp::TexturedQuadLoader()
{
	m_texturedShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/textured.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/textured.frag");
	if (m_texturedShader.link() == false)
	{
		printf("Texture shader Error: %s\n", m_texturedShader.getLastError());
		return false;
	}

	if (m_gridTexture.load("./textures/numbered_grid.tga") == false)
	{
		printf("Failed to load the grid texture correctly\n"); 
		return false;
	}

	m_texturedQuadMesh.InitialiseQuad();


	m_texturedQuadTransform =
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
	m_simpleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (m_simpleShader.link() == false)
	{
		printf("Simple Shader has an Error: %s\n", m_simpleShader.getLastError());
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
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
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
	std::vector<glm::vec4> vertPositions = CreateCircleArray(.5f,glm::vec3(0),12);

	// The verticies will be the fragment amount of the circle plus one to include the centre
	Mesh::Vertex vertices[13];

	// Setting the centre vert pos 
	vertices[0].position = glm::vec4(0,0,0,1);

	// Setting the vert pos for all points around the circle
	for(int i = 1;i < 13; i++)
	{
		vertices[i].position = vertPositions[i];
	}

	// index count is fragment amount * 3
	const int indexCount = 36;
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




	m_diskMesh.Initialise(13, vertices, indexCount, indices);

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
	Mesh::Vertex vertices[5];

	vertices[0].position = { 0.0f,	1,	0.0f,	1 }; // Top

	vertices[1].position = { -.5f,	0,	-.5f,	1 }; // back left
	vertices[2].position = { 0.5f,	0,	-.5f,	1 }; // back right
	vertices[3].position = { 0.5f,	0,	0.5f,	1 }; // font right
	vertices[4].position = { -.5f,	0,	0.5f,	1 }; // front left

	unsigned int indices[30] =
	{
		3,4,1,1,2,3,
		3,0,4,4,0,1,
		1,0,2,2,0,3


	};

	m_pyramidMesh.Initialise(5, vertices, 30, indices);

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

bool ComputerGraphicsApp::ConeLoader()
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

	const int segments = 12;
	// Positions of a circle not including the centre
	std::vector<glm::vec4> vertPositions = CreateCircleArray(.5f, glm::vec3(0), segments);

	// The verticies will be the fragment amount of the circle plus one to include the centre

	Mesh::Vertex vertices[segments + 2];
	// Setting the centre vert pos 

	// Setting the vert pos for all points around the circle
	for (int i = 1;i < segments + 1; i++)
	{
		vertices[i].position = vertPositions[i];
	}

	// index count is fragment amount * 3
	const int indexCount = segments * 6;
	unsigned int indices[indexCount];
	int indexOffset = 0;
	vertices[0].position = glm::vec4(0, 0, 0, 1);
	vertices[segments+1].position = glm::vec4(0, 0, -1, 1);

	// The draw order starts at 0 and index then counts up,
	// every 3rd number will also be 0, then the number before 3rd will repeat.
	// When the last number is reached, to complete the circle the draw order must finish at 1
	// e.g. If there were 12 segements indices would be:
	//		0,1,2,0,2,3,0,3,4,0...10,11,0,11,12,1 
	indices[0] = 0;
	for (int i = 1; i < indexCount / 2; i++)
	{
		if (i == (indexCount/2) - 1)
		{
			indices[i] = 1;
		}
		else if (i % 3 == 0)
		{
			indices[i] = 0;
			indexOffset += 2;
		}
		else
		{
			indices[i] = i - indexOffset;
		}
	}

	for (int i = (indexCount / 2); i < indexCount; i++)
	{
		if (i == indexCount - 1)
		{
			indices[i] = 1;
		}
		else if (i % 3 == 0)
		{
			indices[i] = segments+1;
			indexOffset += 2;
		}
		else
		{
			indices[i] = i - indexOffset;
		}
	}

		m_coneMesh.Initialise(14, vertices, indexCount, indices);

		// This is a 10 'unit' wide quad
		m_coneTransform =
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

void ComputerGraphicsApp::TexturedQuadDraw(glm::mat4 pvm)
{
	// Bind the shader
	m_texturedShader.bind();

	//Bind the transform
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);

	//Bind the texture location
	m_texturedShader.bindUniform("diffuseTexture",0);

	//Bind the texture to a specific location
	//m_gridTexture.bind(0);

	m_renderTarget.getTarget(0).bind(0);

	m_texturedQuadMesh.Draw();
}

void ComputerGraphicsApp::DrawGizmo(glm::mat4 projectionView,glm::mat4 transform 
	, Mesh& gizmoMesh,glm::vec3 position)
{
	glm::mat4 mat
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		position.x,position.y,position.z,1
	};

	SimpleDraw(projectionView*(transform*mat), gizmoMesh);
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

bool ComputerGraphicsApp::SpearLoader()
{
	if (m_spearMesh.load("./soulspear/soulspear.obj",true,true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}
	m_spearTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };

	return true;
}

void ComputerGraphicsApp::OBJDraw(glm::mat4& pv, glm::mat4& transform, aie::OBJMesh& objMesh)
{
	m_normalShader.bind();


	m_normalShader.bindUniform("CameraPosition",
		glm::vec3(m_viewMatrix[3]));

	//Bind the direction light we defind
	m_normalShader.bindUniform("LightDirection", m_scene->GetLight().direction);
	m_normalShader.bindUniform("AmbientColour", m_ambientLight);
	m_normalShader.bindUniform("LightColour", m_scene->GetLight().colour);

	// Bind texture location
	m_normalShader.bindUniform("diffuseTexture", 0);

	m_normalShader.bindUniform("ProjectionViewModel", pv * transform);

	// bind the transofrm using the one provided
	m_normalShader.bindUniform("ModelMatrix", transform);

	objMesh.draw();
}

bool ComputerGraphicsApp::OBJLoader(aie::OBJMesh& objMesh, glm::mat4& transform, float scale, const char* filepath, const char* filename, bool flipTexture)
{
	std::string path = filepath;
	path += filename;

	if (objMesh.load(path.c_str(), true, flipTexture) == false)
	{
		std::string error = filename;
		error += " Mesh Error!\n";
		printf(error.c_str());
		return false;
	}

	
	transform = {
		scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, scale, 0,
		0, 0, 0, 1
	};

	return true;
}


bool ComputerGraphicsApp::GunLoader()
{
	if (m_gunMesh.load("./gun/M1887.obj", true, true) == false)
	{
		printf("Gun Mesh Error!\n");
		return false;
	}
	m_gunTransform = {
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1 };

	return true;
}

void ComputerGraphicsApp::PhongDraw(glm::mat4 pvm, glm::mat4 transform)
{
	// Bind the phong shader
	m_phongShader.bind();

	// Bind the camera position
	m_phongShader.bindUniform("CameraPosition",
		glm::vec3(glm::inverse(m_viewMatrix)[3]));

	//Bind the direction light we defind
	m_phongShader.bindUniform("LightDirection", m_scene->GetLight().direction);
	m_phongShader.bindUniform("AmbientColour", m_ambientLight);
	m_phongShader.bindUniform("LightColour", m_scene->GetLight().colour);

	// bind the pvm using the one provided
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// bind the transofrm using the one provided
	m_phongShader.bindUniform("ModelMatrix", transform);

	m_spearMesh.draw();
}

void ComputerGraphicsApp::PhongDraw(glm::mat4 pvm, glm::mat4 transform, Mesh& mesh)
{
	// Bind the phong shader
	m_phongShader.bind();

	// Bind the camera position
	m_phongShader.bindUniform("CameraPosition",
		glm::vec3(glm::inverse(m_viewMatrix)[3]));

	//Bind the direction light we defind
	m_phongShader.bindUniform("LightDirection", m_scene->GetLight().direction);
	m_phongShader.bindUniform("AmbientColour", m_ambientLight);
	m_phongShader.bindUniform("LightColour", m_scene->GetLight().colour);

	// bind the pvm using the one provided
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// bind the transofrm using the one provided
	m_phongShader.bindUniform("ModelMatrix", transform);

	mesh.Draw();
}
