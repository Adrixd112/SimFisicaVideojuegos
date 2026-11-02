#include "ParticleSystem.h"
#include "BetterParticle.h"

ParticleSystem::ParticleSystem() :occupancy(0)
{
	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++) {
		particles[i] = BetterParticle();
		emptySpaces.push(STATIC_MAX_PARTICLE_COUNT-i-1);
	}

}

BetterParticle* ParticleSystem::addParticle(const Vector3D& pos, const Vector3D& v, const Vector3D& a, float deathCountdown, double damping, double w)
{
	if (emptySpaces.empty())	return nullptr;
	particles[emptySpaces.top()] = BetterParticle(pos, v, a, deathCountdown, damping, w);
	emptySpaces.pop();
	return &particles[emptySpaces.top()];
}

BetterParticle* ParticleSystem::addParticle(const BetterParticle& particle)
{
	if (emptySpaces.empty())	return nullptr;
	particles[emptySpaces.top()] = particle;
	emptySpaces.pop();
	return &particles[emptySpaces.top()];
}



void ParticleSystem::updateParticles(float dt)
{
	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++) {
		if (particles[i].alive)
		{
			particles[i].Integrate(dt);

			if(!particles[i].alive) emptySpaces.push(i);
		}
	}
}
