#include "Instance.h"
#include <glm/ext.hpp>
#include "Scene.h"
#include "OBJMesh.h"
#include <Texture.h>
#include "SimpleCamera.h"
#include "ComputerGraphicsApp.h"

Instance::Instance(glm::mat4 transform, aie::OBJMesh* mesh, aie::ShaderProgram* shader)
{
}

void Instance::Draw(Scene* scene)
{
	// Set the shader pipeline
	m_shader->bind();

	// Bind all relevant uniforms for our shaders
	auto pvm = scene->GetCamera()->GetProjectionMatrix(
		scene->GetWindowSize().x, scene->GetWindowSize().y)*
		scene->GetCamera()->GetViewMatrix()*m_transform;

	// bind the transofrm using the one provided
	m_shader->bindUniform("ModelMatrix", m_transform);
	m_shader->bindUniform("ProjectionViewModel", pvm);

	m_shader->bindUniform("CameraPosition",glm::vec3(
		glm::inverse(scene->GetCamera()->GetViewMatrix())[3]));

	//Bind the direction light we defind
	m_shader->bindUniform("LightDirection", scene->GetLight().direction);
	m_shader->bindUniform("AmbientColour", scene->GetLight().colour);
	m_shader->bindUniform("LightColour", scene->GetAmbienColourLight());




}
