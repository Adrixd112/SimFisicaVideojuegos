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

Vector2D ParticleEmitter::NormalBidimensionalDistribution(float sigma)

{
	float dx = nDistribution(generator) * sigma;
	return Vector2D(dx, dx);
}

Vector2D ParticleEmitter::CircularUniformDistribution(float radius)
{
	float dx = uDistribution(generator) * radius;
	float alpha = uDistribution(generator) * TWO_PI;
	return Vector2D(dx * cos(alpha), dx * sin(alpha));
}

Vector2D ParticleEmitter::SquaredUniformDistribution(const Vector2D& firstCorner, const Vector2D& oppositeCorner)
{
	return Vector2D(firstCorner.x + uDistribution(generator) * (oppositeCorner.x - firstCorner.x), firstCorner.x + uDistribution(generator) * (oppositeCorner.y - firstCorner.y));
}

Vector3D ParticleEmitter::NormalBidimensionalDistribution_Oriented(const Vector3D& dir, float sigma)
{
	Vector2D relativePos = NormalBidimensionalDistribution(sigma);

	return  relativePos.RotateVectorToDirPlane(dir);
}

Vector3D ParticleEmitter::CircularUniformDistribution_Oriented(const Vector3D& dir, float radius)
{
	Vector2D relativePos = CircularUniformDistribution(radius);

	return  relativePos.RotateVectorToDirPlane(dir);
}

Vector3D ParticleEmitter::SquaredUniformDistribution_Oriented(const Vector3D& dir, float w, float h)
{
	Vector2D relativePos = SquaredUniformDistribution(Vector2D(w / 2, h / 2), Vector2D(-w / 2, -h / 2));

	return  relativePos.RotateVectorToDirPlane(dir);
}

void ParticleEmitter_Rectangular_Ortogonal::SetEmittingFunction(const Vector3D& dir, float w, float h, float pps, const BetterParticlePadre& p, ParticleSystem* mySystem)
{
	double timeForNextParticle = deathCountdown;
	double timeBetweenParticles = 1 / pps;

	BetterParticleCopy pc = p;
	extraUpdateFunc = [ mySystem, timeForNextParticle, timeBetweenParticles, dir, w, h, pc](BetterParticle<decltype(this)> *self, double dt) mutable
		{
			self->GenericEmittingFunctionCall(mySystem, timeForNextParticle, timeBetweenParticles, dir, w, h, pc);
		};
}

void ParticleEmitter_Rectangular_Ortogonal::GenericEmittingFunctionCall(ParticleSystem* mySystem, double timeForNextParticle, double timeBetweenParticles, const Vector3D& dir, float w, float h, const BetterParticlePadre& p) {
	std::cout << "tfnp:" << timeForNextParticle << " dcountd:" << deathCountdown << "\n";
	while (timeForNextParticle > deathCountdown) {
		timeForNextParticle -= timeBetweenParticles;

		BetterParticlePadre* particleReturned = mySystem->addParticle(p);
		
		if(particleReturned)
		{
			particleReturned->v.RotateVectorToDirPlane(dir);
			particleReturned->transform.p = SquaredUniformDistribution_Oriented(dir, w, h);
		}
	}
}
