#include "ParticleSystem.h"
#include "BetterParticle.h"

ParticleSystem::ParticleSystem() :active(true), forceGeneratorsActive(true)
{
	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++) {
		particles[i] = nullptr;
		emptySpaces.push(STATIC_MAX_PARTICLE_COUNT - i - 1);
	}
	for (int i = 0; i < STATIC_MAX_FORCEGEN_COUNT;i++) {
		forceGenerators[i] = nullptr;
		emptyForceGeneratorSpaces.push(STATIC_MAX_FORCEGEN_COUNT - i - 1);
	}

}

ParticleSystem::~ParticleSystem()
{
	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++) {
		delete particles[i];
	}
	
	for (int i = 0; i < STATIC_MAX_FORCEGEN_COUNT;i++) {
		delete forceGenerators[i];	
	}
	
}

BetterParticle<void>* ParticleSystem::addParticle(const Vector3D& pos, const Vector3D& v,  float deathCountdown, double damping, double w)
{
	if (emptySpaces.empty())	return nullptr;
	int posInParticleArray = emptySpaces.top();emptySpaces.pop();
	particles[posInParticleArray] = new BetterParticle<void>(pos, v, deathCountdown, damping, w);
	return static_cast<BetterParticle<void>*>(particles[posInParticleArray]);
}

ForceGenerator* ParticleSystem::addForceGenerator(ForceGenerator* fg)
{
	if (emptyForceGeneratorSpaces.empty())	return nullptr;
	int posInForceGenArray = emptyForceGeneratorSpaces.top();emptyForceGeneratorSpaces.pop();
	forceGenerators[posInForceGenArray] = fg;
	return fg;
}

bool ParticleSystem::removeForceGenerator(ForceGenerator* fg,bool doesDelete)
{
	bool encontrado = false;
	for (int i = 0;i < STATIC_MAX_FORCEGEN_COUNT;i++) {
		if (forceGenerators[i] = fg) 
		{
			forceGenerators[i] = nullptr;
			encontrado = true;
		}
	}
	if (encontrado&&doesDelete) delete fg;
	return encontrado;
}

void ParticleSystem::updateParticles(float dt)
{
	if (!active) return;

	for (int i = 0; i < STATIC_MAX_PARTICLE_COUNT;i++) {
		if (particles[i] != nullptr)
			if (particles[i]->GetAlive())
			{
				particles[i]->a = Vector3D::Zero;
				if(particles[i]->w!=0)
				{
					if (forceGeneratorsActive) {
						for (int fi = 0;fi < STATIC_MAX_FORCEGEN_COUNT;fi++) {
							ForceGenerator* fgen = forceGenerators[fi];
							if (fgen != nullptr && fgen->getActive()) {
								particles[i]->a += fgen->CalculateForce(particles[i]) * particles[i]->w;//a = F/m = F*w
							}
						}
					}
				}

				particles[i]->Integrate(dt);

				if (!particles[i]->GetAlive())
				{
					emptySpaces.push(i);
					delete particles[i];
					particles[i] = nullptr;
				}
			}
	}
}
