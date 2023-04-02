#pragma once
#include "SimpleCamera.h"
#include <Input.h>
class FlyCamera : public SimpleCamera
{
public:
	FlyCamera();
	~FlyCamera();

	void Update(float deltaTime) override;
	void SetFastSpeed(float speed) { m_cameraFastSpeed = speed; }
	void SetdefaultSpeed(float speed) { m_cameraDefaultSpeed = speed; }
	glm::mat4 SetViewMatrix() override;

protected:
	float m_turningSpeed = glm::radians(180.f);

	float m_phi;
	float m_theta;

	float m_cameraFastSpeed = 15;
	float m_cameraDefaultSpeed = 5;
	// Last position of the mouse
	glm::vec2 m_lastMouse;
private:

};

