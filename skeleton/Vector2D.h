#pragma once
#include <PxPhysicsAPI.h>
#include <cmath>
#include<iostream>
#include "Vector3D.h"
class Vector2D
{
public:
	float x, y;
	Vector2D()noexcept :x(0), y(0) {}
	Vector2D(const Vector2D& v) noexcept :x(v.x), y(v.y) {}
	Vector2D(const Vector3D& v) noexcept : x(v.x), y(v.y) {}
	Vector2D(float x, float y)noexcept :x(x), y(y) {}
	Vector2D(const physx::PxVec3& v)noexcept :x(v.x), y(v.y) {}

	float magnitude() const noexcept { return sqrt(x * x + y * y); }
	Vector2D normalize() const noexcept { const float mag = magnitude(); return Vector2D(x / mag, y / mag); }

	//Cross y dot product
	//No Static
	float dot(const Vector2D& v) const noexcept { return x * v.x + y * v.y; }
	//Static
	static float dot(const Vector2D& u, const Vector2D& v)  noexcept { return u.x * v.x + u.y * v.y; }

	//operadores
	Vector2D operator*(float scalar) const noexcept { return Vector2D(x * scalar, y * scalar); }
	Vector2D operator/(float scalar) const noexcept { return Vector2D(x / scalar, y / scalar); }

	Vector2D operator+(const Vector2D& other) const noexcept { return Vector2D(x + other.x, y + other.y); }
	Vector2D operator-(const Vector2D& other) const noexcept { return Vector2D(x - other.x, y - other.y); }
	Vector2D operator-() const noexcept { return Vector2D(-x, -y); }
	void operator=(const Vector2D& other) noexcept { x = other.x; y = other.y; }

	Vector2D& operator+=(const Vector2D& other) noexcept { x += other.x; y += other.y; ; return *this; }
	Vector2D& operator-=(const Vector2D& other) noexcept { x -= other.x; y -= other.y; ; return *this; }

	bool operator==(const Vector2D& other) const noexcept { return x == other.x && y == other.y; }

	operator physx::PxVec2() const { return physx::PxVec2(x, y); }

	/// @brief rota un vector libre en (x,y,0) para mantenerme fijo relativo a a un plano que ha rotado alrededor de un eje que pasa por el (0,0,0)
	/// @param planeCoordinates: Coords del vector respecto del plano
	/// @param dirFin: normal del plano rotado
	/// @param dirIni: normal del plano inicial default plano z = 0, n = (0,0,1)
	/// @return el vector libre rotado en coordenadas.
	static Vector3D RotateVectorToDirPlane(const Vector2D& planeCoordinates, const Vector3D& dirFin, const Vector3D& dirIni = Vector3D(0, 0, 1));

	/// @brief roto como un vector libre en (x,y,0) para que se mantenga fijo relativo a a un plano que ha rotado alrededor de un eje que pasa por el (0,0,0)
	/// @param dirFin: normal del plano rotado
	/// @param dirIni: normal del plano inicial default plano z = 0, n = (0,0,1)
	/// @return el vector libre rotado en coordenadas.
	Vector3D RotateVectorToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni = Vector3D(0, 0, 1));

};
inline std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
	os << "(" << v.x << ", " << v.y << ")";
	return os;
}
inline Vector2D operator*(float scalar, const Vector2D& v) noexcept { return v * scalar; }
