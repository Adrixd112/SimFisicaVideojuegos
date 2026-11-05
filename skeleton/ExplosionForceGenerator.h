#pragma once
#include "ForceGenerator.h"
class ExplosionForceGenerator :public ForceGenerator
{

	float potencia;//me matas por las unidades, pero me lo estoy inventando

	float explosionRadius;

	float timeSinceExplosionStarted;

	const float explosionTimeConstant = 1;


	Vector3D explosionOrigin;


	
public:
	ExplosionForceGenerator(Vector3D origin, float potencia) : explosionOrigin(origin),potencia(potencia){};
	virtual Vector3D CalculateForce(Particle* p);

};

