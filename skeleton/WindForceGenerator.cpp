#include "WindForceGenerator.h"
#include "Particle.h"
Vector3D WindForceGenerator::CalculateForce(Particle* p)
{
    Vector3D dv = windvel - p->v;
    Vector3D posmax = origin + areaSize / 2;
    Vector3D posmin = origin - areaSize / 2;
    if (Vector3D(p->transform.p) > posmin && Vector3D(p->transform.p) <= posmax)
    {
        return Vector3D(k1 * dv + k2 * dv.magnitude() * dv);
    }
    else return Vector3D::Zero;
}
