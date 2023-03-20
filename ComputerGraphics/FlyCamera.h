#pragma once
#include "SimpleCamera.h"
#include <Input.h>
class FlyCamera : public SimpleCamera
{
public:
	FlyCamera();
	~FlyCamera();

	void Update(float deltaTime);
	void SetFastSpeed(float speed) { m_cameraFastSpeed = speed; }
	void SetdefaultSpeed(float speed) { m_cameraDefaultSpeed = speed; }

protected:
	float m_turningSpeed = glm::radians(180.f);

	float m_cameraFastSpeed = 10;
	float m_cameraDefaultSpeed = 5;
	// Last position of the mouse
	glm::vec2 m_lastMouse;
private:

};

