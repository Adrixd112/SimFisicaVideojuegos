#include "GravityForceGenerator.h"
#include "Particle.h"
Vector3D GravityForceGenerator::CalculateForce(Particle* p)
{
    return Vector3D(0,accel/p->w,0);
}
