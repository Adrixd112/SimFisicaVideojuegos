#include "Proyectile.h"


void Proyectile::RecalculateSimulateds()
{
	v = vReal * vRealProp;

	w = wReal * pow(vRealProp, 2);
	a = aReal * pow(vRealProp, 2);

}

Proyectile::Proyectile(const Vector3D& pos, double vRealProp, const Vector3D& v, const Vector3D& a, double damping,double w) :vReal(v), aReal(a),  wReal(w), vRealProp(vRealProp), Particle(pos,v,a,damping,w)
{
	RecalculateSimulateds();
}
Proyectile::Proyectile(const Vector3D& pos, double vRealProp, double damping, const Vector3D& v, const Vector3D& a) : Proyectile(pos,vRealProp, v, a, damping) {

}
Proyectile::Proyectile(double w, const Vector3D& pos, double vRealProp, const Vector3D& v, const Vector3D& a, double damping) :Proyectile(pos,vRealProp, v, a, damping, w)
{
}
