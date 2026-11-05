#pragma once
#include "Particle.h"
class Proyectile :protected Particle
{
	friend class Scene;
public:

	Vector3D vReal;
	Vector3D aReal;


	double wReal; // 1/m

	double vRealProp; //prop vsimulada/vreal

private:
	void RecalculateSimulateds();
	bool hasStartedMoving;
	void (Particle::* integrateFunc)(double);
protected:

	Proyectile() {};
	Proyectile(const Vector3D& pos, double vRealProp, const Vector3D& v = Vector3D::Zero,  double damping = 0.97, double w = 1);
	Proyectile(const Vector3D& pos,  double damping, double vRealProp, const Vector3D& v = Vector3D::Zero);
	Proyectile(double w, const Vector3D& pos, double vRealProp, const Vector3D& v = Vector3D::Zero,  double damping = 0.97);
	Proyectile(double m,const Vector3D& pos, const Vector3D& v = Vector3D::Zero, double vReal = 10,  double damping = 0.97);
	Proyectile(double m, const Vector3D& pos, const Vector3D& dirV, double vReal, double vSim,  double damping = 0.97);

	~Proyectile();
};

