#pragma once
#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh() : 
		m_triCount(0),m_vao(0),m_vbo(0), m_ibo(0){}
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	// Will be used to make a simple quad
	void InitialiseQuad();

	// Will be used for Post Processing
	void InitialiseFullscreenQuad();

	// will be used for implamenting a primitive
	void Initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = nullptr);

	virtual void Draw();



protected:
	unsigned int m_triCount;
	unsigned int m_vao; // the Vertex Array object
	unsigned int m_vbo; // The Vertex Buffer Object
	unsigned int m_ibo; // The Index Buffer Object

};

