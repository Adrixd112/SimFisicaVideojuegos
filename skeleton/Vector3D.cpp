#include "Vector3D.h"

Vector3D Vector3D::RotateVectorToDirPlane(const Vector3D& planeRelativeCoordinates, const Vector3D& dirFin, const Vector3D& dirIni)
{
	Vector3D axis = dirIni.cross(dirFin);
	double angleCos = dirIni.dot(dirFin);
	double angleSin = axis.magnitude();

	Vector3D posFin = planeRelativeCoordinates * angleCos + axis.cross(planeRelativeCoordinates) * angleSin + axis * axis.dot(planeRelativeCoordinates) * (1 - angleCos);
	return posFin;
}

Vector3D Vector3D::RotateVectorToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni )
{
	return RotateVectorToDirPlane(*this, dirFin, dirIni);
}

void Vector3D::RotatedToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni)
{
	*this = RotateVectorToDirPlane(*this, dirFin, dirIni);
}

