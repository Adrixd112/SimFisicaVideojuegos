#include "ExplosionForceGenerator.h"
#include"Particle.h"
#include <cmath>
Vector3D ExplosionForceGenerator::CalculateForce(Particle* p)
{
    Vector3D dv = p->transform.p - explosionOrigin;
    if (dv.magnitude() < explosionRadius) {
         return potencia / pow(dv.magnitude(), 2) * dv * pow(std::exp(1), -(currentTime-explosionStartTime) / explosionTimeConstant);
    }
    else {
        return Vector3D::Zero;
    }
}

void ExplosionForceGenerator::explode()
{
    explosionStartTime = currentTime;
}

void ExplosionForceGenerator::update(double relativeTime)
{
    currentTime = relativeTime;
}
