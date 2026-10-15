#pragma once
#include "Particle.h"
#include <functional>
class BetterParticle :public Particle
{
protected:
	bool alive;
	float deathCountdown;

	std::function<void()> extraUpdateFunc;
	std::function<bool()> deathConditions;
	std::function<void()> onDeath;
	std::function<bool()> isSleep;
public:
	

protected:


	bool getAlive() { return alive; }
	void Integrate(double dt) override;
	

};

