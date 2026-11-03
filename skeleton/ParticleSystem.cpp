#include "ParticleSystem.h"
#include "BetterParticle.h"

ParticleSystem::ParticleSystem() :occupancy(0)
{
	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++) {
		particles[i] = BetterParticlePadre();
		emptySpaces.push(STATIC_MAX_PARTICLE_COUNT-i-1);
	}

}

BetterParticlePadre* ParticleSystem::addParticle(const Vector3D& pos, const Vector3D& v, const Vector3D& a, float deathCountdown, double damping, double w)
{
	if (emptySpaces.empty())	return nullptr;
	particles[emptySpaces.top()] = BetterParticlePadre(pos, v, a, deathCountdown, damping, w);
	emptySpaces.pop();
	return &particles[emptySpaces.top()];
}

BetterParticlePadre* ParticleSystem::addParticle(const BetterParticlePadre& particle)
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
