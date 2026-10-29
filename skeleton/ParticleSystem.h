#pragma once
#include "ParticleEmitter.h";
#include "BetterParticle.h";
#include <vector>;
#include <array>;
#include <queue>;

constexpr size_t STATIC_MAX_PARTICLE_COUNT = 1000;
constexpr size_t STATIC_MAX_EMITTER_COUNT = 100;
class ParticleSystem
{
	BetterParticle particles[STATIC_MAX_PARTICLE_COUNT];

	ParticleEmitter emitters[STATIC_MAX_EMITTER_COUNT];

	std::queue<int,std::array<int,STATIC_MAX_PARTICLE_COUNT>> emptySpaces;

	std::queue<int, std::array<int, STATIC_MAX_EMITTER_COUNT>> emptyEmitters;

	size_t occupancy;

public:

	ParticleSystem();

	bool addParticle(BetterParticle*& particleReturned,const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1);

	bool addEmitter(ParticleEmitter*& emitter);

	void updateParticles(float dt); 

};

