#pragma once
#include "BetterParticle.h"

class Proyectile :protected BetterParticle<Proyectile>
{
	friend class Scene;
	friend class ParticleSystem;
public:



private:
	void RecalculateSimulateds(const Vector3D& vReal,double wReal,double vRealProp);
	
	float vRealProp2;
protected:

	Proyectile() {};
	Proyectile(const Vector3D& pos, double vRealProp, const Vector3D& v = Vector3D::Zero, double deathCountdown = -1,  double damping = 0.97, double w = 1);
	Proyectile(const Vector3D& pos,  double damping, double vRealProp, const Vector3D& v = Vector3D::Zero);
	Proyectile(double w, const Vector3D& pos, double vRealProp, const Vector3D& v = Vector3D::Zero, double deathCountdown= -1,  double damping = 0.97);
	Proyectile(double m,const Vector3D& pos, const Vector3D& v = Vector3D::Zero, double vReal = 10,  double damping = 0.97);
	Proyectile(double m, const Vector3D& pos, const Vector3D& dirV, double vReal, double vSim,double deathCountdown = -1,  double damping = 0.97);

	virtual void Integrate(double dt) override {
		this->a += Vector3D(0, (vRealProp2 - 1) * -9.81, 0); //para contrarestar la gravedad
		BetterParticle<Proyectile>::Integrate(dt);
	}
};

