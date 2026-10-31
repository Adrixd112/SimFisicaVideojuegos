#include "ParticleSystem.h"
#include "BetterParticle.h"

ParticleSystem::ParticleSystem() :occupancy(0)
{
	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++) {
		particles[i] = BetterParticle();
		emptySpaces.push(i);
	}

}

bool ParticleSystem::addParticle(BetterParticle*& particleReturned, const Vector3D& pos, const Vector3D& v, const Vector3D& a, float deathCountdown, double damping, double w)
{
	if (emptySpaces.empty())	return false;
	particles[emptySpaces.front()].~BetterParticle();
	particles[emptySpaces.front()] = BetterParticle(pos, v, a, deathCountdown, damping, w);
	particleReturned = &particles[emptySpaces.front()];
	return true;
}

bool ParticleSystem::addParticle(const BetterParticle& particle, BetterParticle*& particleReturned)
{
	if (emptySpaces.empty())	return false;
	particles[emptySpaces.front()].~BetterParticle();
	particles[emptySpaces.front()] = particle;
	particleReturned = &particles[emptySpaces.front()];
	return true;
}

bool ParticleSystem::addParticle(const BetterParticle& particle)
{
	if (emptySpaces.empty())	return false;
	particles[emptySpaces.front()].~BetterParticle();
	particles[emptySpaces.front()] = particle;
	return true;
}



void ParticleSystem::updateParticles(float dt)
{
	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++) {
		if (particles[i].alive)
		{
			particles[i].Integrate(dt);
		}
	}
	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++)
	{
		if (!particles[i].alive)
		{
			particles[i].alive = false;
			emptySpaces.push(i);
		}
	}
}
