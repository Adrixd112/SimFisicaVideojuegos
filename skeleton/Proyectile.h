#pragma once
#include "Particle.h"
class Proyectile :protected Particle
{
	friend class Scene;
public:

	Vector3D vReal;
	Vector3D aReal;


	double wReal; // 1/m

	double vRealProp;

private:
	void RecalculateSimulateds();
	bool hasStartedMoving;
	void (Particle::* integrateFunc)(double);
protected:

	Proyectile() {};
	Proyectile(const Vector3D& pos, double vRealProp, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, double damping = 0.97, double w = 1);
	Proyectile(const Vector3D& pos,  double damping, double vRealProp, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 });
	Proyectile(double w, const Vector3D& pos, double vRealProp, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, double damping = 0.97);
	~Proyectile();
};

