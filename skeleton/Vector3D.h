#pragma once
#include <PxPhysicsAPI.h>
#include <cmath>
class Vector3D
{
public:
	float x, y, z;
	Vector3D()noexcept :x(0),y(0),z(0) {}
	Vector3D(const Vector3D& v) noexcept :x(v.x), y(v.y), z(v.z) {}
	Vector3D(float x, float y , float z)noexcept :x(x), y(y), z(z) {}
	Vector3D(const physx::PxVec3& v)noexcept :x(v.x), y(v.y), z(v.z) {}

	float magnitude() const noexcept { return sqrt(x * x + y * y + z * z); }
	Vector3D normalize() const noexcept { const float mag = magnitude(); return Vector3D(x / mag, y / mag, z / mag);  }

	//Cross y dot product
	//No Static
	float dot(const Vector3D& v) const noexcept { return x * v.x + y * v.y + z * v.z; }
	Vector3D cross(const Vector3D& v) const noexcept { return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	//Static
	static float dot(const Vector3D& u,const Vector3D& v)  noexcept { return u.x * v.x + u.y * v.y + u.z * v.z; }
	static Vector3D cross(const Vector3D& u, const Vector3D& v)  noexcept { return Vector3D(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x); }

	//operadores
	Vector3D operator*(float scalar) const noexcept { return Vector3D(x * scalar, y * scalar, z * scalar); }
	
	Vector3D operator+(const Vector3D& other) const noexcept { return Vector3D(x + other.x ,y +other.y , z +other.z); }
	Vector3D operator-(const Vector3D& other) const noexcept { return Vector3D(x - other.x, y - other.y, z - other.z); }
	Vector3D operator-() const noexcept { return Vector3D(-x, -y, -z); }
	void operator=(const Vector3D& other) noexcept { x = other.x; y = other.y; z = other.z; }

	Vector3D& operator+=(const Vector3D& other) noexcept { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3D& operator-=(const Vector3D& other) noexcept { x -= other.x; y -= other.y; z -= other.z; return *this; }

	bool operator==(const Vector3D& other) const noexcept { return x == other.x && y == other.y && z == other.z; }

	operator physx::PxVec3() const { return physx::PxVec3(x, y, z); }

};

