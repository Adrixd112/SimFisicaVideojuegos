#pragma once
#include "RenderUtils.hpp"
#include "Vector3D.h"
class Particle
{
	friend class Scene;
public:
	physx::PxTransform transform;
	Vector3D v;
	Vector3D a;

	Vector3D p0;

	double w; // 1/m

	double damping;

	RenderItemP* renderItem;
	


	void setIntegrateEuler() { integrateFunc = &Particle::eulerIntegrate; }
	void setIntegrateSemiEuler() { integrateFunc = &Particle::semiEulerIntegrate; }
	void setIntegrateVerlet() { integrateFunc = &Particle::verletIntegrate; }
private:
	bool hasStartedMoving;
	void (Particle::* integrateFunc)(double);
protected:

	Particle() {};
	Particle(const Vector3D& pos, const Vector3D& v = {0,0,0}, const Vector3D& a = { 0,0,0 }, double damping = 0.97);
	Particle(const Vector3D& pos, double damping, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 });
	~Particle();

	void Integrate(double dt);

	void eulerIntegrate(double dt);
	void semiEulerIntegrate(double dt);
	void verletIntegrate(double dt);
};

