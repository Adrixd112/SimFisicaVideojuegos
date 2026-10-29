#include "ParticleEmitter.h"

#include <random>
#include <numbers>

const double TWO_PI = 6.283185307179586;
std::mt19937 ParticleEmitter::generator{ std::random_device{}() };

std::uniform_real_distribution<float> ParticleEmitter::uDistribution(0.0f, 1.0f);

std::normal_distribution<float> ParticleEmitter::nDistribution(0.0f, 1.0f);

float ParticleEmitter::UniformDistribution(float a, float b) {


	return a + uDistribution(generator) * (b - a);
}
float ParticleEmitter::NormalDistribution(float mean, float sigma) {

	return mean + nDistribution(generator) * sigma;
}

Vector2D ParticleEmitter::NormalBidimensionalDistribution( float sigma)

{
	float dx = nDistribution(generator) * sigma;
	return Vector2D( dx, dx);
}

Vector2D ParticleEmitter::CircularUniformDistribution( float radius)
{
	float dx = uDistribution(generator) * radius;
	float alpha = uDistribution(generator) * TWO_PI;
	return Vector2D(dx*cos(alpha),dx*sin(alpha));
}

Vector2D ParticleEmitter::SquaredUniformDistribution(const Vector2D& firstCorner, const Vector2D& oppositeCorner)
{
	return Vector2D(firstCorner.x + uDistribution(generator) * (oppositeCorner.x - firstCorner.x), firstCorner.x + uDistribution(generator) * (oppositeCorner.y - firstCorner.y));
}

Vector3D ParticleEmitter::NormalBidimensionalDistribution_Oriented(const Vector3D& origin, const Vector3D& dir, float sigma)
{
	Vector2D relativePos = NormalBidimensionalDistribution(sigma);
	
	return RotateVectorToDirPlane(origin,dir,relativePos);
}

Vector3D ParticleEmitter::CircularUniformDistribution_Oriented(const Vector3D& origin, const Vector3D& dir, float radius)
{
	Vector2D relativePos = CircularUniformDistribution(radius);

	return RotateVectorToDirPlane(origin, dir, relativePos);
}

Vector3D ParticleEmitter::SquaredUniformDistribution_Oriented(const Vector3D& origin, const Vector3D& dir, float w, float h)
{
	Vector2D relativePos = SquaredUniformDistribution(Vector2D(w / 2, h / 2), Vector2D(-w / 2, -h / 2));

	return RotateVectorToDirPlane(origin, dir, relativePos);
}

Vector3D ParticleEmitter::RotateVectorToDirPlane(const Vector3D& origin, const Vector3D& dir, const Vector2D& planeCoordinates)
{
	Vector3D axis = Vector3D(0, 0, 1).cross(dir);
	double angleCos = Vector3D(0, 0, 1).dot(dir);
	double angleSin = axis.magnitude();

	Vector3D posFin = (Vector3D)planeCoordinates * angleCos + axis.cross(planeCoordinates) * angleSin + axis * axis.dot(planeCoordinates) * (1 - angleCos);
	return posFin;
}
