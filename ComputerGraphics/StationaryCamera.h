#pragma once
#include "SimpleCamera.h"
class StationaryCamera :public SimpleCamera
{
public:
	StationaryCamera();
	~StationaryCamera();
	
	void SetRotation(glm::vec3 eularAngles);
protected:
private:
	
};

