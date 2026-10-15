#include "Proyectile.h"
#include <iostream>

void Proyectile::RecalculateSimulateds()
{
	v = vReal * vRealProp;
	const double vRealProp2 = pow(vRealProp, 2);

	w = wReal * vRealProp2;
	a = aReal * vRealProp2;

	std::cout << "vre:" << vReal <<"mod: "<<vReal.magnitude() << " vs:" << v <<"mod: " << v.magnitude() << "\n";
}

Proyectile::Proyectile(const Vector3D& pos, double vRealProp, const Vector3D& vReal, const Vector3D& a, double damping,double w) :vReal(vReal), aReal(a),  wReal(w), vRealProp(vRealProp), Particle(pos, damping)
{
	RecalculateSimulateds();
	renderItem->color = { 1,0,0,1 };

}
Proyectile::Proyectile(const Vector3D& pos, double vRealProp, double damping, const Vector3D& vReal, const Vector3D& a) : Proyectile(pos,vRealProp, vReal, a, damping) {

}
Proyectile::Proyectile(double w, const Vector3D& pos, double vRealProp, const Vector3D& vReal, const Vector3D& a, double damping) :Proyectile(pos,vRealProp, vReal, a, damping, w)
{
}

Proyectile::Proyectile(double m, const Vector3D& pos, const Vector3D& vReal, double vSim, const Vector3D& a, double damping):Proyectile(1/m,pos, vSim/vReal.magnitude(),vReal,a,damping)
{
	
}

Proyectile::Proyectile(double m, const Vector3D& pos, const Vector3D& dirV, double vReal, double vSim, const Vector3D& a, double damping):Proyectile(1/m,pos,vSim/vReal,vReal*dirV,a,damping)
{
}


