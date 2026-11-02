#pragma once
#include "ParticleEmitter.h";
#include "BetterParticle.h";
#include <vector>;
#include "Utils.h";


constexpr size_t STATIC_MAX_PARTICLE_COUNT = 1000;

class ParticleSystem
{
	BetterParticle particles[STATIC_MAX_PARTICLE_COUNT];

	Stack<int,STATIC_MAX_PARTICLE_COUNT> emptySpaces;



	size_t occupancy;

public:

	ParticleSystem();
	~ParticleSystem() {}

	BetterParticle* addParticle(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1);

	BetterParticle* addParticle(const BetterParticle& particle);



	void updateParticles(float dt); 

};

