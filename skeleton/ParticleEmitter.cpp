#include "ParticleEmitter.h"

#include <random>
#include <numbers>

const double TWO_PI = 6.283185307179586;
std::mt19937 ParticleEmitterOperations::generator{ std::random_device{}() };

std::uniform_real_distribution<float> ParticleEmitterOperations::uDistribution(0.0f, 1.0f);

std::normal_distribution<float> ParticleEmitterOperations::nDistribution(0.0f, 1.0f);

float ParticleEmitterOperations::UniformDistribution(float a, float b) {


	return a + uDistribution(generator) * (b - a);
}
float ParticleEmitterOperations::NormalDistribution(float mean, float sigma) {

	return mean + nDistribution(generator) * sigma;
}

Vector2D ParticleEmitterOperations::NormalBidimensionalDistribution(float sigma)

{
	float dx = nDistribution(generator) * sigma;
	return Vector2D(dx, dx);
}

Vector2D ParticleEmitterOperations::CircularUniformDistribution(float radius)
{
	float dx = uDistribution(generator) * radius;
	float alpha = uDistribution(generator) * TWO_PI;
	return Vector2D(dx * cos(alpha), dx * sin(alpha));
}

Vector2D ParticleEmitterOperations::SquaredUniformDistribution(const Vector2D& firstCorner, const Vector2D& oppositeCorner)
{
	return Vector2D(firstCorner.x + uDistribution(generator) * (oppositeCorner.x - firstCorner.x), firstCorner.x + uDistribution(generator) * (oppositeCorner.y - firstCorner.y));
}

Vector3D ParticleEmitterOperations::NormalBidimensionalDistribution_Oriented(const Vector3D& dir, float sigma)
{
	Vector2D relativePos = NormalBidimensionalDistribution(sigma);

	return  relativePos.RotateVectorToDirPlane(dir);
}

Vector3D ParticleEmitterOperations::CircularUniformDistribution_Oriented(const Vector3D& dir, float radius)
{
	Vector2D relativePos = CircularUniformDistribution(radius);

	return  relativePos.RotateVectorToDirPlane(dir);
}

Vector3D ParticleEmitterOperations::SquaredUniformDistribution_Oriented(const Vector3D& dir, float w, float h)
{
	Vector2D relativePos = SquaredUniformDistribution(Vector2D(w / 2, h / 2), Vector2D(-w / 2, -h / 2));

	return  relativePos.RotateVectorToDirPlane(dir);
}


