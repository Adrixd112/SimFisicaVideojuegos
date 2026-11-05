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


	virtual void SetRenderItem(const RenderItem* rip);
	virtual void SetRenderItemPrefab(const RenderItem* ri);
	virtual void SetRenderItemPrefab(const RenderItem_Prefab& ri);

	virtual RenderItem* GetRenderItem() const { return renderItem; }
protected:
	RenderItemP* renderItem;

private:
	bool hasStartedMoving;
	void (Particle::* integrateFunc)(double);
protected:

	Particle(): renderItem(nullptr) {};
	Particle(const Particle& other);
	Particle(const Vector3D& pos, const Vector3D& v = {0,0,0}, const Vector3D& a = Vector3D::Zero, double damping = 0.97, double w = 1, RenderItemP* renderItem = nullptr, bool hasRenderItem = true);
	Particle(const Vector3D& pos, double damping, const Vector3D& v = Vector3D::Zero, const Vector3D& a = Vector3D::Zero);
	Particle(double w, const Vector3D& pos, const Vector3D& v = Vector3D::Zero, const Vector3D& a = Vector3D::Zero, double damping = 0.97);
	Particle& operator=(const Particle& other);
	~Particle();

	virtual void Integrate(double dt);

	void eulerIntegrate(double dt);
	void semiEulerIntegrate(double dt);
	void verletIntegrate(double dt);
};

