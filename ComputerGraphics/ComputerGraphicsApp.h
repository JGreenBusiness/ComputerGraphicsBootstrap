#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Shader.h"

#include "OBJMesh.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>


class ComputerGraphicsApp : public aie::Application {
public:

	ComputerGraphicsApp();
	virtual ~ComputerGraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	bool LaunchShaders();
	void ImGUIRefresher();

	bool QuadLoader();
	bool BoxLoader();
	bool CylinderLoader();
	std::vector<glm::vec4> CreateCircleArray(float radius, glm::vec3 pos, int fragments);
	bool PyramidLoader();

	bool BunnyLoader();
	void BunnyDraw(glm::mat4 pvm);

	void PhongDraw(glm::mat4 pvm, glm::mat4 transform);
	void PhongDraw(glm::mat4 pvm, glm::mat4 transform,Mesh& mesh);
	void SimpleDraw(glm::mat4 pvm, Mesh& mesh);

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::ShaderProgram	m_simpleShader;
	aie::ShaderProgram	m_colourShader;
	aie::ShaderProgram	m_phongShader;

	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;
	
	Mesh				m_boxMesh;
	glm::mat4			m_boxTransform;
    
	Mesh				m_pyramidMesh;
	glm::mat4			m_pyramidTransform;
    	
	  
	Mesh				m_cylinderMesh;
	glm::mat4			m_cylinderTransform;
    	
	

	aie::OBJMesh	m_bunnyMesh;
	glm::mat4		m_bunnyTransform;

	glm::vec3			m_shapeRotAxis;
	float				m_shapeRot;
	struct Light
	{
		glm::vec3 direction;
		glm::vec3 colour;
	};

	Light m_light;
	glm::vec3 m_ambientLight;

};


