#include "BetterParticle.h"

void BetterParticle::Integrate(double dt)
{
	if (!isSleep || !isSleep(this))
	{
		if(extraUpdateFunc) extraUpdateFunc(this,dt);

		Particle::Integrate(dt);

		deathCountdown -= dt;
		if (hasLifetime && deathCountdown <= 0) alive = false;
	}

	if(willDieConditions) alive = alive && !willDieConditions(this);

	if (!alive && onDeath) onDeath(this);
}
