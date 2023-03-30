#include "FlyCamera.h"

FlyCamera::FlyCamera() : SimpleCamera()
{

}

FlyCamera::~FlyCamera()
{
}

void FlyCamera::Update(float deltaTime)
{
	//aie::Input* input = aie::Input::getInstance();
	//float thetaR = glm::radians(m_theta);
	//float phiR = glm::radians(m_phi);

	//glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
	//	glm::cos(phiR) * glm::sin(thetaR));
	//glm::vec3 right(-glm::sin(thetaR), 0, glm::cos(thetaR));

	//forward = glm::vec3(1, 0, 0);
	//glm::vec3 up(0, 1, 0);

	//// We will used WASD to move and the Q and E to go up and down

	//float camSpeed = m_cameraDefaultSpeed;
	//if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
	//{
	//	camSpeed = m_cameraFastSpeed;
	//}

	//glm::vec3 pos = (glm::vec3)m_worldTransoform[3];
	//if (input->isKeyDown(aie::INPUT_KEY_W))
	//{
	//	pos += forward * deltaTime * camSpeed;
	//}
	//if (input->isKeyDown(aie::INPUT_KEY_S))
	//{
	//	pos -= forward * deltaTime * camSpeed;
	//}
	//if (input->isKeyDown(aie::INPUT_KEY_A))
	//{
	//	pos -= right * deltaTime * camSpeed;
	//}
	//if (input->isKeyDown(aie::INPUT_KEY_D))
	//{
	//	pos += right * deltaTime * camSpeed;
	//}

	//if (input->isKeyDown(aie::INPUT_KEY_Q))
	//{
	//	pos -= up * deltaTime * camSpeed;
	//}
	//if (input->isKeyDown(aie::INPUT_KEY_E))
	//{
	//	pos += up * deltaTime * camSpeed;
	//}

	//SetPosition(pos);



	//// Get the mouse coordinates
	//float mx = input->getMouseX();
	//float my = input->getMouseY();


	//// If the right button is held down, increment theta and phi (rotate)
	//if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	//{
	//	m_theta += m_turningSpeed * (mx - m_lastMouse.x) * deltaTime;
	//	m_phi += m_turningSpeed * (my - m_lastMouse.y) * deltaTime;
	//}

	//m_lastMouse = glm::vec2(mx, my);

}