#include "Vector2D.h"
Vector3D Vector2D::RotateVectorToDirPlane(const Vector2D& planeRelativeCoordinates, const Vector3D& dirFin, const Vector3D& dirIni)
{
	Vector3D axis = dirIni.cross(dirFin);
	double angleCos = dirIni.dot(dirFin);
	double angleSin = axis.magnitude();

	Vector3D posFin = (Vector3D)planeRelativeCoordinates * angleCos + axis.cross(planeRelativeCoordinates) * angleSin + axis * axis.dot(planeRelativeCoordinates) * (1 - angleCos);
	return posFin;
}

Vector3D Vector2D::RotateVectorToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni)
{
	return RotateVectorToDirPlane(*this, dirFin, dirIni);
}

