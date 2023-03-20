#pragma once
#include "SimpleCamera.h"
#include <Input.h>
class FlyCamera : public SimpleCamera
{
public:
	FlyCamera();
	~FlyCamera();

	void Update(float deltaTime);

protected:
	float m_turningSpeed = glm::radians(180.f);

	float m_cameraSpeed = 5;
	// Last position of the mouse
	glm::vec2 m_lastMouse;
private:

};

