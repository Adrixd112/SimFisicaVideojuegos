#pragma once
#include <PxPhysicsAPI.h>
#include <cmath>
#include<iostream>


class Vector3D;

class Vector2D
{
public:
	static const Vector2D Zero;
	float x, y;
	Vector2D()noexcept :x(0), y(0) {}
	Vector2D(const Vector2D& v) noexcept :x(v.x), y(v.y) {}
	Vector2D(const Vector3D& v);
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
	static Vector3D GetRotatedVectorToDirPlane(const Vector2D& planeCoordinates, const Vector3D& dirFin, const Vector3D& dirIni);

	/// @brief roto como un vector libre en (x,y,0) para que se mantenga fijo relativo a a un plano que ha rotado alrededor de un eje que pasa por el (0,0,0)
	/// @param dirFin: normal del plano rotado
	/// @param dirIni: normal del plano inicial default plano z = 0, n = (0,0,1)
	/// @return el vector libre rotado en coordenadas.
	Vector3D GetRotatedVectorToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni);

};
inline std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
	os << "(" << v.x << ", " << v.y << ")";
	return os;
}
inline Vector2D operator*(float scalar, const Vector2D& v) noexcept { return v * scalar; }

class Vector3D
{
public:
	static const Vector3D Zero;
	static const Vector3D Infinity;

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
	bool operator<(const Vector3D& other) const noexcept { return x < other.x && y < other.y && z < other.z; }
	bool operator>(const Vector3D& other) const noexcept { return x > other.x && y > other.y && z > other.z; }
	bool operator>=(const Vector3D& other) const noexcept { return !(*this < other); }
	bool operator<= (const Vector3D & other) const noexcept { return !(*this > other); }

	operator physx::PxVec3() const { return physx::PxVec3(x, y, z); }


	/// @brief rota un vector libre para que se mantenga fijo relativo a a un plano que ha rotado alrededor de un eje que pasa por el (0,0,0)
	/// @param planeCoordinates: Coords del vector respecto del plano
	/// @param dirFin: normal del plano rotado
	/// @param dirIni: normal del plano inicial default plano z = 0, n = (0,0,1)
	/// @return el vector libre rotado en coordenadas.
	static Vector3D GetRotatedVectorToDirPlane(const Vector3D& planeCoordinates, const Vector3D& dirFin, const Vector3D& dirIni = {0,0,1});
	/// @brief rota un vector libre igual a mí para que se mantenga fijo relativo a a un plano que ha rotado alrededor de un eje que pasa por el (0,0,0)
/// @param dirFin: normal del plano rotado
/// @param dirIni: normal del plano inicial default plano z = 0, n = (0,0,1)
/// @return yo si hubiera rotado.
	Vector3D GetRotatedVectorToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni = { 0,0,1 });
	/// @brief roto para mantenerme fijo relativo a a un plano que ha rotado alrededor de un eje que pasa por el (0,0,0)
/// @param dirFin: normal del plano rotado
/// @param dirIni: normal del plano inicial default plano z = 0, n = (0,0,1)
	void RotateToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni = { 0,0,1 });
};
inline std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}
inline Vector3D operator*(float scalar, const Vector3D& v) noexcept { return v * scalar; }

inline Vector3D Vector2D::GetRotatedVectorToDirPlane(const Vector2D& planeRelativeCoordinates, const Vector3D& dirFin, const Vector3D& dirIni = { 0,0,1 })
{
	Vector3D axis = dirIni.cross(dirFin);
	double angleCos = dirIni.dot(dirFin);
	double angleSin = axis.magnitude();

	Vector3D posFin = (Vector3D)planeRelativeCoordinates * angleCos + axis.cross(planeRelativeCoordinates) * angleSin + axis * axis.dot(planeRelativeCoordinates) * (1 - angleCos);
	return posFin;
}

inline Vector3D Vector2D::GetRotatedVectorToDirPlane(const Vector3D& dirFin, const Vector3D& dirIni = { 0,0,1 })
{
	return GetRotatedVectorToDirPlane(*this, dirFin, dirIni);
}

inline Vector2D::Vector2D(const Vector3D& v) : x(v.x), y(v.y) {}