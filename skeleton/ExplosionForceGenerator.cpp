#include "ExplosionForceGenerator.h"
#include"Particle.h"
#include <cmath>
Vector3D ExplosionForceGenerator::CalculateForce(Particle* p)
{
    Vector3D dv = p->transform.p - explosionOrigin;
    if()
    return potencia / pow(dv.magnitude(), 2) * dv * pow(std::exp(1),-timeSinceExplosionStarted/explosionTimeConstant);
}
