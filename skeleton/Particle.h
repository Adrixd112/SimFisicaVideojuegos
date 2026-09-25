#pragma once
#include "RenderUtils.hpp"
#include "Vector3D.h"
class Particle
{
public:
	Vector3D p;
	Vector3D v;
	Vector3D a;

	Vector3 pAnt;

	double w; // 1/m

	RenderItem* renderItem;

	void Integrate(double dt);
private:
	void eulerIntegrate(double dt);
	void semiEulerIntegrate(double dt);
	void verletIntegrate(double dt);
};

