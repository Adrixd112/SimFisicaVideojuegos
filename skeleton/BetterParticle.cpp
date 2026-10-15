#include "BetterParticle.h"

void BetterParticle::Integrate(double dt)
{
	if (!isSleep())
	{
		extraUpdateFunc();
		Particle::Integrate(dt);
	}

	alive = deathConditions();

	if (!alive) onDeath();
}
