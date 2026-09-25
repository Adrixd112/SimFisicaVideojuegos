#include "Particle.h"

void Particle::eulerIntegrate(double dt)
{
	p = p + v * dt;
	v = v + a * dt;
}

void Particle::semiEulerIntegrate(double dt)
{
	v = v + a * dt;
	p = p + v * dt;
}

void Particle::verletIntegrate(double dt)
{
	p = 2*p  −xi−1 + h2 ·a;

}
