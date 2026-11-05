#include "ParticleSystem.h"
#include "BetterParticle.h"

ParticleSystem::ParticleSystem() :occupancy(0)
{
	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++) {
		particles[i] = nullptr;
		emptySpaces.push(STATIC_MAX_PARTICLE_COUNT-i-1);
	}

}

BetterParticle<void>* ParticleSystem::addParticle(const Vector3D& pos, const Vector3D& v, const Vector3D& a, float deathCountdown, double damping, double w)
{
	if (emptySpaces.empty())	return nullptr;
	int posInParticleArray = emptySpaces.top();emptySpaces.pop();
	particles[posInParticleArray] = new BetterParticle<void>(pos, v, a, deathCountdown, damping, w);
	return static_cast<BetterParticle<void>*>(particles[posInParticleArray]);
}





void ParticleSystem::updateParticles(float dt)
{
	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++) {
		if(particles[i]!=nullptr)
		if (particles[i]->GetAlive())
		{
			particles[i]->Integrate(dt);

			if(!particles[i]->GetAlive()) 
			{
				emptySpaces.push(i);
				delete particles[i];
				particles[i] = nullptr;
			}
		}
	}
}
