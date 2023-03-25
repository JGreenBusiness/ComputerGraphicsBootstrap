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
	m_theta = eularAngles.y;
	m_phi = eularAngles.x;
}
