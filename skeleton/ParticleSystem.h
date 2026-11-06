#pragma once
#include "ParticleEmitter.h";
#include "BetterParticle.h";
#include "ForceGenerator.h"

#include <memory>
#include <vector>;
#include "Utils.h";


constexpr size_t STATIC_MAX_PARTICLE_COUNT = 10000;
constexpr size_t STATIC_MAX_FORCEGEN_COUNT = 10;

class ParticleSystem
{
	GenericBetterParticle* particles[STATIC_MAX_PARTICLE_COUNT];

	Stack<int,STATIC_MAX_PARTICLE_COUNT> emptySpaces;

	std::shared_ptr<ForceGenerator> forceGenerators[STATIC_MAX_PARTICLE_COUNT];

	Stack<int, STATIC_MAX_FORCEGEN_COUNT> emptyForceGeneratorSpaces;

	bool forceGeneratorsActive;

	bool active;
public:

	ParticleSystem() ;
	~ParticleSystem();

	ParticleSystem(const ParticleSystem&) = delete;
	ParticleSystem& operator=(const ParticleSystem&) = delete;

	BetterParticle<void>* addParticle(const Vector3D& pos, const Vector3D& v = Vector3D::Zero,  float deathCountdown = -1, double damping = 0.97, double w = 1);

	template<typename BP>
	BP* addParticle(const Particle_Prefab<BP>& particle)
	{
		if (emptySpaces.empty())	return nullptr;
		int posInParticleArray = emptySpaces.top();emptySpaces.pop();
		if (particles[posInParticleArray] != nullptr) delete particles[posInParticleArray];
		particles[posInParticleArray] = new BP(particle);
		return static_cast<BP*>(particles[posInParticleArray]);
	}

	std::shared_ptr<ForceGenerator> addForceGenerator(std::shared_ptr<ForceGenerator> fg);
	
	bool removeForceGenerator(std::shared_ptr<ForceGenerator> fg);

	void updateParticles(float dt,float sceneT); 

	void setUseForcesActive(bool useForcesActive) {
		this->forceGeneratorsActive = useForcesActive;
	}

	bool getUseForcesActive() {
		return forceGeneratorsActive;
	}

	void setActive(bool active) {
		this->active = active;
	}

	bool getActive() {
		return active;
	}
};

