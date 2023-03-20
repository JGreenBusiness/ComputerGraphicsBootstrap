#include "FlyCamera.h"

FlyCamera::FlyCamera() : SimpleCamera()
{

}

FlyCamera::~FlyCamera()
{
}

void FlyCamera::Update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
		glm::cos(phiR) * glm::sin(thetaR));
	glm::vec3 right(-glm::sin(thetaR), 0, glm::cos(thetaR));
	glm::vec3 up(0, 1, 0);

	// We will used WASD to move and the Q and E to go up and down

	float camSpeed = 1;
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
	{
		camSpeed = m_cameraSpeed;
	}

	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		m_position += forward * deltaTime * camSpeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		m_position -= forward * deltaTime * camSpeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		m_position -= right * deltaTime * camSpeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		m_position += right * deltaTime * camSpeed;
	}

	if (input->isKeyDown(aie::INPUT_KEY_Q))
	{
		m_position -= up * deltaTime * camSpeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_E))
	{
		m_position += up * deltaTime * camSpeed;
	}

	// Get the mouse coordinates
	float mx = input->getMouseX();
	float my = input->getMouseY();


	// If the right button is held down, increment theta and phi (rotate)
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_theta += m_turningSpeed * (mx - m_lastMouse.x) * deltaTime;
		m_phi += m_turningSpeed * (my - m_lastMouse.y) * deltaTime;
	}

	m_lastMouse = glm::vec2(mx, my);

}