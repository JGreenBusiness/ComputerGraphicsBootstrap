#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Shader.h"

#include "OBJMesh.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include "FlyCamera.h"
#include "StationaryCamera.h"
#include "Texture.h"
#include "Scene.h"
#include "Instance.h"

class ComputerGraphicsApp : public aie::Application {
public:

	ComputerGraphicsApp();
	virtual ~ComputerGraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	bool LaunchShaders();
	void ImGUIRefresher();

	bool QuadLoader();
	bool TexturedQuadLoader();
	bool BoxLoader();
	bool DiskLoader();
	std::vector<glm::vec4> CreateCircleArray(float radius, glm::vec3 pos, int fragments);
	bool PyramidLoader();
	bool ConeLoader();


	bool BunnyLoader();
	void BunnyDraw(glm::mat4 pvm);

	bool SpearLoader();

	// For Textured OBJs
	void OBJDraw(glm::mat4& pvm, glm::mat4& Transform, aie::OBJMesh& objMesh);
	bool OBJLoader(aie::OBJMesh& objMesh, glm::mat4& transofrm,
		float scale, const char* filepath, const char* filename,
		bool flipTexture);

	bool GunLoader();

	void PhongDraw(glm::mat4 pvm, glm::mat4 transform);
	void PhongDraw(glm::mat4 pvm, glm::mat4 transform,Mesh& mesh);
	void SimpleDraw(glm::mat4 pvm, Mesh& mesh);
	void TexturedQuadDraw(glm::mat4 pvm);

	void DrawGizmo(glm::mat4 projectionView, glm::mat4 transform, Mesh& gizmoMesh,
		glm::vec3 position);

	Scene*		m_scene;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::Texture m_gridTexture;

	aie::ShaderProgram	m_simpleShader;
	aie::ShaderProgram	m_colourShader;
	aie::ShaderProgram	m_phongShader;
	aie::ShaderProgram	m_texturedShader;
	aie::ShaderProgram	m_shader;

	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;
	
	Mesh				m_texturedQuadMesh;
	glm::mat4			m_texturedQuadTransform;
	aie::Texture		m_quadTexture;
	bool				m_isTextured;
	
	Mesh				m_boxMesh;
	glm::mat4			m_boxTransform;
    
	Mesh				m_pyramidMesh;
	glm::mat4			m_pyramidTransform;
    	
	  
	Mesh				m_diskMesh;
	glm::mat4			m_diskTransform;
    	  
	Mesh				m_coneMesh;
	glm::mat4			m_coneTransform;
    	
	

	aie::OBJMesh	m_bunnyMesh;
	glm::mat4		m_bunnyTransform;
	
	aie::OBJMesh	m_spearMesh;
	glm::mat4		m_spearTransform;
	
	aie::OBJMesh	m_gunMesh;
	glm::mat4		m_gunTransform;


	glm::vec3		m_shapeRotAxis;
	float			m_shapeRot;

	glm::mat4		m_OBJTransform;

	SimpleCamera*		m_camera;
	FlyCamera*			m_flyCamera;
	StationaryCamera*	m_stillCamera;

	bool m_enableFlyCam;

	glm::vec3 m_camPos;
	glm::vec3 m_camRot;

	glm::vec3 m_ambientLight;
	Light* m_mainLight;
	Light* m_pointLight1;
	Light* m_pointLight2;


};


