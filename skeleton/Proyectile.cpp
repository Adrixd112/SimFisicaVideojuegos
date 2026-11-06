#include "Proyectile.h"
#include <iostream>

void Proyectile::RecalculateSimulateds(const Vector3D& vReal,double wReal,double vRealProp)//prop vsimulada/vreal)
{
	v = vReal * vRealProp;
	vRealProp2 = pow(vRealProp, 2);

	w = wReal * vRealProp2;

	std::cout << "vre:" << vReal <<"mod: "<<vReal.magnitude() << " vs:" << v <<"mod: " << v.magnitude() << "\n";
}

Proyectile::Proyectile(const Vector3D& pos, double vRealProp, const Vector3D& vReal, double deathCountdown, double damping,double w) :
	BetterParticle<Proyectile>(pos,Vector3D::Zero, damping,w)
{
	RecalculateSimulateds(vReal,w,vRealProp);
	renderItem->color = { 1,0,0,1 };

}
Proyectile::Proyectile(const Vector3D& pos, double vRealProp, double damping, const Vector3D& vReal ) : Proyectile(pos,vRealProp, vReal,  damping) {

}
Proyectile::Proyectile(double w, const Vector3D& pos, double vRealProp, const Vector3D& vReal, double deathCountdown,  double damping) :Proyectile(pos,vRealProp, vReal,deathCountdown,  damping, w)
{
}

Proyectile::Proyectile(double m, const Vector3D& pos, const Vector3D& vReal, double vSim,  double damping):Proyectile(1/m,pos, vSim/vReal.magnitude(),vReal,damping)
{
	
}

Proyectile::Proyectile(double m, const Vector3D& pos, const Vector3D& dirV, double vReal, double vSim,double deathCountdown,  double damping):Proyectile(1/m,pos,vSim/vReal,vReal*dirV,deathCountdown,damping)
{
}


