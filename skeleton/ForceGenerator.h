#pragma once
#include "Vector3D.h"
class Particle;
class ForceGenerator
{
protected:
	bool active;
public:
	ForceGenerator() :active(true) {};
	virtual Vector3D CalculateForce(Particle* p) = 0;
	virtual void update(double dt) {};

	void setActive(bool active) {
		this->active = active;
	}

	bool getActive() {
		return active;
	}
};

