#pragma once
#include "ParticleEmitter.h";
#include "BetterParticle.h";
#include <vector>;
#include "Utils.h";


constexpr size_t STATIC_MAX_PARTICLE_COUNT = 1000;

class ParticleSystem
{
	GenericBetterParticle particles[STATIC_MAX_PARTICLE_COUNT];

	Stack<int,STATIC_MAX_PARTICLE_COUNT> emptySpaces;



	size_t occupancy;

public:

	ParticleSystem();
	~ParticleSystem() {}

	BetterParticle<void>* addParticle(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1);

	template<typename BP>
	IsOrInheritsFromBetterParticle<BP>* addParticle(const BP& particle)
	{
		if (emptySpaces.empty())	return nullptr;
		int posInParticleArray = emptySpaces.top();emptySpaces.pop();
		particles[posInParticleArray] = particle;
		return static_cast<IsOrInheritsFromBetterParticle<BP>*>(&particles[posInParticleArray]);
	}

	void updateParticles(float dt); 

};

