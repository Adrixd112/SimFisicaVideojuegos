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

bool ParticleSystem::addEmitter(ParticleEmitter*& emitter)
{
	if (emptyEmitters.empty())	return false;
	emitters[emptyEmitters.front()].~ParticleEmitter();
	emitters[emptyEmitters.front()] = *emitter;
	emitter = &emitters[emptyEmitters.front()];
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
