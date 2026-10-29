#include "BetterParticle.h"

void BetterParticle::Integrate(double dt)
{
	if (!isSleep || !isSleep())
	{
		if(extraUpdateFunc) extraUpdateFunc(dt);

		Particle::Integrate(dt);

		deathCountdown -= dt;
		if (hasLifetime && deathCountdown <= 0) alive = false;
	}

	if(willDieConditions) alive = alive && !willDieConditions();

	if (!alive && onDeath) onDeath();
}
