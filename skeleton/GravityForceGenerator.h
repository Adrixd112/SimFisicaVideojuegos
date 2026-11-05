#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator :public ForceGenerator
{
	float accel;
public:
	GravityForceGenerator(float accel = -9.81) : accel(accel) {};
	virtual Vector3D CalculateForce(Particle* p);
};

