#include "Vector3D.h"

const Vector3D Vector3D::Zero = Vector3D(0, 0, 0);
const Vector3D Vector3D::Infinity = Vector3D(INFINITY, INFINITY, INFINITY);
const Vector2D Vector2D::Zero = Vector2D(0, 0);

Vector3D Vector3D::GetRotatedVectorToDirPlane(const Vector3D& planeRelativeCoordinates, const Vector3D& dirFin, const Vector3D& dirIni)
{
	Vector3D axis = dirIni.cross(dirFin);
	double angleCos = dirIni.dot(dirFin);
	double angleSin = axis.magnitude();

	Vector3D posFin = planeRelativeCoordinates * angleCos + axis.cross(planeRelativeCoordinates) * angleSin + axis * axis.dot(planeRelativeCoordinates) * (1 - angleCos);
	return posFin;
}

Vector3D Vector3D::GetRotatedVectorToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni )
{
	return GetRotatedVectorToDirPlane(*this, dirFin, dirIni);
}

void Vector3D::RotateToDirPlane (const Vector3D& dirFin, const Vector3D& dirIni)
{
	*this = GetRotatedVectorToDirPlane(*this, dirFin, dirIni);
}

