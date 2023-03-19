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
	void QuadDraw(glm::mat4 pvm);
	
	bool BoxLoader();
	void BoxDraw(glm::mat4 pvm);

	bool BunnyLoader();
	void BunnyDraw(glm::mat4 pvm);

	void PhongDraw(glm::mat4 pvm, glm::mat4 transform);

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
	glm::vec3			m_boxRotAxis;
	float				m_boxRot;
	

	aie::OBJMesh	m_bunnyMesh;
	glm::mat4		m_bunnyTransform;

	struct Light
	{
		glm::vec3 direction;
		glm::vec3 colour;
	};

	Light m_light;
	glm::vec3 m_ambientLight;

};


