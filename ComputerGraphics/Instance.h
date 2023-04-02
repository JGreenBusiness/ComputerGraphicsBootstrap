#pragma once
#include <glm/glm.hpp>

class SimpleCamera;
class Scene;
class Light;

namespace aie 
{
	class OBJMesh;
	class ShaderProgram;
}

class Instance
{
public:
	Instance(glm::mat4 transform, aie::OBJMesh* mesh,
		aie::ShaderProgram* shader);
	Instance(glm::vec3 position, glm::vec3 eularAngles, glm::vec3 scale,
		aie::OBJMesh* mesh, aie::ShaderProgram* shader);
	~Instance(){};

	void Draw(Scene* scene);

	static glm::mat4 MakeTransform(glm::vec3 position,
		glm::vec3 eularAngles, glm::vec3 scale);

	glm::mat4 SetTransform(glm::vec3 position,
		glm::vec3 eularAngles, glm::vec3 scale)
	{ return m_transform =
		MakeTransform(position,eularAngles,scale);
	}
	glm::mat4 GetTransform() { return m_transform; }
protected:
	glm::mat4 m_transform;
	aie::OBJMesh* m_mesh;
	aie::ShaderProgram* m_shader;

};

