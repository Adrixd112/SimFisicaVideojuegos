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


	void setIntegrateEuler() { integrateFunc = &Particle::eulerIntegrate; }
	void setIntegrateSemiEuler() { integrateFunc = &Particle::semiEulerIntegrate; }
	void setIntegrateVerlet() { integrateFunc = &Particle::verletIntegrate; }


	void SetRenderItem(const RenderItem_Prefab& rip);
	void SetRenderItem(const RenderItem* ri);

	RenderItem* GetRenderItem() const { return renderItem; }
protected:
	RenderItemP* renderItem;

private:
	bool hasStartedMoving;
	void (Particle::* integrateFunc)(double);
protected:

	Particle(): renderItem(nullptr) {};
	Particle(const Particle& other);
	Particle(const Vector3D& pos, const Vector3D& v = {0,0,0}, const Vector3D& a = { 0,0,0 }, double damping = 0.97, double w = 1, RenderItemP* renderItem = nullptr, bool hasRenderItem = true);
	Particle(const Vector3D& pos, double damping, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 });
	Particle(double w, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, double damping = 0.97);
	~Particle();

	virtual void Integrate(double dt);

	void eulerIntegrate(double dt);
	void semiEulerIntegrate(double dt);
	void verletIntegrate(double dt);
};

