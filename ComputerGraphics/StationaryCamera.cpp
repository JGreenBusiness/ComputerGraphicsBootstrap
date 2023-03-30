#include "StationaryCamera.h"
#include <glm/ext.hpp>
StationaryCamera::StationaryCamera() : SimpleCamera()
{
}

StationaryCamera::~StationaryCamera()
{
}

void StationaryCamera::SetRotation(glm::vec3 eularAngles)
{
	//m_worldTransoform = GetWorldTransform(GetPosition(), eularAngles, glm::vec3(1));
}
