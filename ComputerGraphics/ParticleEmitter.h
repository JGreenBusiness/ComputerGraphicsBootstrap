#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/ext.hpp>
#include <gl_core_4_4.h>

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 colour;

	float size;
	float lifespan;
	float lifetime;
};

struct ParticleVertex
{
	glm::vec4 position;
	glm::vec4 colour;
};

class ParticleEmitter
{
public:
	ParticleEmitter();
	ParticleEmitter(unsigned int _maxParticles, unsigned int _emmitRate,
		float _lifetimeMin, float _lifetimeMax,
		float _velocityMin, float _velocityMax,
		float _startSize, float _endSize,
		const glm::vec4& _startcolour,
		const glm::vec4& _endColour);
	virtual ~ParticleEmitter();


	/// <summary> Initialises particle effect.</summary>
	void Initialise(unsigned int _maxParticles, unsigned int _emmitRate,
		float _lifetimeMin, float _lifetimeMax,
		float _velocityMin, float _velocityMax,
		float _startSize, float _endSize,
		const glm::vec4& _startcolour,
		const glm::vec4& _endColour);

	/// <summary> Emit's particle effect.</summary>
	void Emit();

	void Update(float _dt, const glm::mat4& _cameraTransform);
	void Draw();



protected:
	Particle* m_particles;
	unsigned int m_firstDead;
	unsigned int m_maxParticles;
	
	unsigned int m_vao, m_vbo, m_ibo;
	ParticleVertex* m_vertexData;

	glm::vec3 m_position;

	float m_emitTimer;
	float m_emitRate;
	
	float m_lifeSpanMin;
	float m_lifeSpanMax;

	float m_velocityMin;
	float m_velocityMax;

	float m_startSize;
	float m_endSize;

	glm::vec4 m_startColour;
	glm::vec4 m_endColour;

	glm::vec3 m_gravity = { 0,0,0 };
	bool m_hasGravity = false;

private:
};

