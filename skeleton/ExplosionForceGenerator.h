#pragma once
#include "ForceGenerator.h"
class ExplosionForceGenerator :public ForceGenerator
{

	float potencia;

	float explosionRadius;

	float explosionStartTime;

	float currentTime;

	const float explosionTimeConstant = 1;


	Vector3D explosionOrigin;


	
public:
	ExplosionForceGenerator(Vector3D origin, float potencia,float radio) : explosionOrigin(origin),potencia(potencia),explosionRadius(radio),explosionStartTime(-1000),currentTime(0){};
	virtual Vector3D CalculateForce(Particle* p);
	void explode();
	virtual void update(double relativeTime)override;
};

