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
#include "RenderTarget.h"

#include "ParticleEmitter.h"


class ComputerGraphicsApp : public aie::Application {
public:

	ComputerGraphicsApp();
	virtual ~ComputerGraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	/// <summary> Launches all shaders and loads all meshes. Returns fasle at any point there is a failure to load something.</summary>
	bool LaunchShaders();
	void ImGUIRefresher();

	/// <summary> Loads a quad mesh using simple shader</summary>
	bool QuadLoader();

	/// <summary> loads a textued quad mesh using textured shader</summary>
	bool TexturedQuadLoader();

	/// <summary> launches a box mesh using simple shader</summary>
	bool BoxLoader();

	/// <summary> launches a disk mesh using simple shader</summary>
	bool DiskLoader();

	
	/// <summary> Loads a pyramid mesh using simple shader</summary>
	bool PyramidLoader();

	/// <summary> Loads a Cone mesh using phong shader</summary>
	bool ConeLoader();

	/// <summary> Creates an array of points for a circle</summary>
	std::vector<glm::vec4> CreateCircleArray(float radius, glm::vec3 pos, int fragments);

	/// <summary> Loads a Bunny mesh using phong shader.</summary>
	bool BunnyLoader();
	/// <summary> Draws bunny mesh</summary>
	void BunnyDraw(glm::mat4 pvm);

	/// <summary> Loads spear mesh</summary>
	bool SpearLoader();

	// For Textured OBJs
	void OBJDraw(glm::mat4& pvm, glm::mat4& Transform, aie::OBJMesh& objMesh);

	/// <summary> Loads any OBJ file's mesh</summary>
	bool OBJLoader(aie::OBJMesh& objMesh, glm::mat4& transofrm,
		float scale, const char* filepath, const char* filename,
		bool flipTexture);

	/// <summary> Loads gun mesh</summary>
	bool GunLoader();

	/// <summary> Initialises phong shader and loads spear mesh.</summary>
	void PhongDraw(glm::mat4 pvm, glm::mat4 transform);

	/// <summary> Initialises phong shader and loads and draws a mesh.</summary>
	void PhongDraw(glm::mat4 pvm, glm::mat4 transform,Mesh& mesh);

	/// <summary> Initialises simple shader and loads and draws a mesh.</summary>
	void SimpleDraw(glm::mat4 pvm, Mesh& mesh);

	/// <summary> Initialises textured shader and loads and draws a quad mesh.</summary>
	void TexturedQuadDraw(glm::mat4 pvm);

	/// <summary> Initialises and draws a mesh with a simple shader.</summary>
	void DrawGizmo(glm::mat4 projectionView, glm::mat4 transform, Mesh& gizmoMesh,
		glm::vec3 position);

	Scene*		m_scene;

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::Texture m_gridTexture;

	// Shaders
	aie::ShaderProgram	m_simpleShader;
	aie::ShaderProgram	m_colourShader;
	aie::ShaderProgram	m_phongShader;
	aie::ShaderProgram	m_texturedShader;
	aie::ShaderProgram	m_normalShader;
	aie::ShaderProgram	m_postProcessShader;
	aie::ShaderProgram	m_particleShader;

	// Post effects
	int m_postProcessEffect = -1;

	aie::RenderTarget	m_renderTarget;

	// Mesh related
	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;
	Mesh				m_fullScreenQuad; // quad which is over the screen
	
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
    	
	

	aie::OBJMesh		m_bunnyMesh;
	glm::mat4			m_bunnyTransform;
	
	aie::OBJMesh		m_spearMesh;
	glm::mat4			m_spearTransform;
	
	aie::OBJMesh		m_gunMesh;
	glm::mat4			m_gunTransform;

	// Current selected instance variables
	glm::vec3			m_objEular;
	glm::vec3			m_objPos;
	glm::vec3			m_objScale;

	glm::mat4			m_OBJTransform;

	int m_selectedInstance;
	std::vector<Instance*> m_instances;

	// Camera reated
	SimpleCamera*		m_camera; // Current camera
	FlyCamera*			m_flyCamera;
	StationaryCamera*	m_stillCamera;

	bool				m_enableFlyCam;

	glm::vec3			m_camPos;
	glm::vec3			m_camRot;

	// Scene Lighting related
	glm::vec3 m_ambientLight;
	Light* m_mainLight;

	Light* m_pointLight1;
	Light* m_pointLight2;

	// Partical related
	ParticleEmitter*		m_emitter;
	glm::mat4				m_particlemitTransform;

};


