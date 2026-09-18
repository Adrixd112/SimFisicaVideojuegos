#pragma once
#include <PxPhysicsAPI.h>
#include <cmath>
class Vector3D
{
public:
	float x, y, z;
	Vector3D():x(0),y(0),z(0) {}
	Vector3D(const Vector3D& v) :x(v.x), y(v.y), z(v.z) {}
	Vector3D(float x, float y , float z) :x(x), y(y), z(z) {}
	Vector3D(const physx::PxVec3& v) :x(v.x), y(v.y), z(v.z) {}

	float magnitude() const { return sqrt(x * x + y * y + z * z); }
	Vector3D normalize() const { float mag = magnitude(); return Vector3D(x / mag, y / mag, z / mag);  }
	float dot(const Vector3D& v) const { return x * v.x + y * v.y + z * v.z; }
	Vector3D cross(const Vector3D& v) const {return Vector3D() }

	bool operator=(const Vector3D& other) const { return x == other.x && y == other.y && z == other.z; }
	Vector3D operator+(const Vector3D& other) const { return Vector3D(x + other.x ,y +other.y , z +other.z); }
	Vector3D& operator+=(const Vector3D& other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3D operator-(const Vector3D& other) const { return Vector3D(x - other.x, y - other.y, z - other.z); }
	Vector3D operator-() const { return Vector3D(-x, -y, -z); }
	Vector3D operator*(float scalar) const { return Vector3D(x *scalar, y *scalar, z *scalar); }
	operator physx::PxVec3() const { return physx::PxVec3(x, y, z); }
};

