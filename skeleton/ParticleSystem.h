#pragma once
#include "ParticleEmitter.h";
#include "BetterParticle.h";
#include <vector>;
#include "Utils.h";


constexpr size_t STATIC_MAX_PARTICLE_COUNT = 3000;

class ParticleSystem
{
	GenericBetterParticle* particles[STATIC_MAX_PARTICLE_COUNT];

	Stack<int,STATIC_MAX_PARTICLE_COUNT> emptySpaces;



	size_t occupancy;

public:

	ParticleSystem();
	~ParticleSystem() {}

	BetterParticle<void>* addParticle(const Vector3D& pos, const Vector3D& v = Vector3D::Zero, const Vector3D& a = Vector3D::Zero, float deathCountdown = -1, double damping = 0.97, double w = 1);

	template<typename BP>
	BP* addParticle(const Particle_Prefab<BP>& particle)
	{
		if (emptySpaces.empty())	return nullptr;
		int posInParticleArray = emptySpaces.top();emptySpaces.pop();
		if (particles[posInParticleArray] != nullptr) delete particles[posInParticleArray];
		particles[posInParticleArray] = new BP(particle);
		return static_cast<BP*>(particles[posInParticleArray]);
	}


	void updateParticles(float dt); 

};

