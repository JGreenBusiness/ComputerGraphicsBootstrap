#pragma once
#include "Application.h"
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
	void DrawPlanet(glm::vec3 _pos, float _radius, glm::vec4 _colour);

	glm::mat4 RotateAround(float radius, const glm::vec3& point, const glm::vec3& axis);

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	std::vector<float> m_planetSizes;

	std::vector <glm::vec3> m_planetPos;

	std::vector <glm::vec4> m_planetColours;

	const glm::mat4* m_mat;

};