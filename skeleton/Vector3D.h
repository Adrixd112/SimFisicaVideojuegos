#pragma once
#include <PxPhysicsAPI.h>
#include <cmath>
#include<iostream>
#include "Vector2D.h"



class Vector3D
{
public:
	float x, y, z;
	Vector3D()noexcept :x(0), y(0), z(0) {}
	Vector3D(const Vector3D& v) noexcept :x(v.x), y(v.y), z(v.z) {}
	Vector3D(const Vector2D& v) :x(v.x), y(v.y), z(0) {}
	Vector3D(float x, float y, float z)noexcept :x(x), y(y), z(z) {}
	Vector3D(const physx::PxVec3& v)noexcept :x(v.x), y(v.y), z(v.z) {}

	~Vector3D() {};
	float magnitude() const noexcept { return sqrt(x * x + y * y + z * z); }
	Vector3D normalize() const noexcept { const float mag = magnitude(); return Vector3D(x / mag, y / mag, z / mag); }

	//Cross y dot product
	//No Static
	float dot(const Vector3D& v) const noexcept { return x * v.x + y * v.y + z * v.z; }
	Vector3D cross(const Vector3D& v) const noexcept { return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	//Static
	static float dot(const Vector3D& u, const Vector3D& v)  noexcept { return u.x * v.x + u.y * v.y + u.z * v.z; }
	static Vector3D cross(const Vector3D& u, const Vector3D& v)  noexcept { return Vector3D(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x); }

	//operadores
	Vector3D operator*(float scalar) const noexcept { return Vector3D(x * scalar, y * scalar, z * scalar); }
	Vector3D operator/(float scalar) const noexcept { return Vector3D(x / scalar, y / scalar, z / scalar); }

	Vector3D operator+(const Vector3D& other) const noexcept { return Vector3D(x + other.x, y + other.y, z + other.z); }
	Vector3D operator-(const Vector3D& other) const noexcept { return Vector3D(x - other.x, y - other.y, z - other.z); }
	Vector3D operator-() const noexcept { return Vector3D(-x, -y, -z); }
	void operator=(const Vector3D& other) noexcept { x = other.x; y = other.y; z = other.z; }

	Vector3D& operator+=(const Vector3D& other) noexcept { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3D& operator-=(const Vector3D& other) noexcept { x -= other.x; y -= other.y; z -= other.z; return *this; }

	bool operator==(const Vector3D& other) const noexcept { return x == other.x && y == other.y && z == other.z; }

	operator physx::PxVec3() const { return physx::PxVec3(x, y, z); }


	/// @brief rota un vector libre para que se mantenga fijo relativo a a un plano que ha rotado alrededor de un eje que pasa por el (0,0,0)
	/// @param planeCoordinates: Coords del vector respecto del plano
	/// @param dirFin: normal del plano rotado
	/// @param dirIni: normal del plano inicial default plano z = 0, n = (0,0,1)
	/// @return el vector libre rotado en coordenadas.
	static Vector3D RotateVectorToDirPlane(const Vector3D& planeCoordinates, const Vector3D& dirFin, const Vector3D& dirIni = {0,0,1});
	/// @brief rota un vector libre igual a mí para que se mantenga fijo relativo a a un plano que ha rotado alrededor de un eje que pasa por el (0,0,0)
/// @param dirFin: normal del plano rotado
/// @param dirIni: normal del plano inicial default plano z = 0, n = (0,0,1)
/// @return yo si hubiera rotado.
	Vector3D RotateVectorToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni = { 0,0,1 });
	/// @brief roto para mantenerme fijo relativo a a un plano que ha rotado alrededor de un eje que pasa por el (0,0,0)
/// @param dirFin: normal del plano rotado
/// @param dirIni: normal del plano inicial default plano z = 0, n = (0,0,1)
	void RotatedToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni = { 0,0,1 });
};
inline std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}
inline Vector3D operator*(float scalar, const Vector3D& v) noexcept { return v * scalar; }

