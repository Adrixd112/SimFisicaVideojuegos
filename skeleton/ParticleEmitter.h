#pragma once
#include "BetterParticle.h"
#include "ParticleSystem.h"
#include <random>

class ParticleEmitterOperations {
private:
	static std::mt19937 generator;
	static std::uniform_real_distribution<float> uDistribution;
	static std::normal_distribution<float> nDistribution;
protected:
	template<typename BP>
	class BetterParticleCopy : public BetterParticle<BP> {
	public:
		BetterParticleCopy(const BetterParticle<BP>& p) :BetterParticle<BP>(p) {};
		BetterParticleCopy<BP>& operator=(const BetterParticle<BP>& p) { BetterParticle<BP>::operator=(p); return *this; }
	};
protected:
	static float UniformDistribution(float a, float b);
	static float NormalDistribution(float mean, float sigma);
	static Vector2D NormalBidimensionalDistribution(float sigma);
	static Vector2D CircularUniformDistribution(float radius);
	static Vector2D SquaredUniformDistribution(const Vector2D& firstCorner, const Vector2D& oppositeCorner);

	static Vector3D NormalBidimensionalDistribution_Oriented(const Vector3D& dir, float sigma);
	static Vector3D CircularUniformDistribution_Oriented(const Vector3D& dir, float radius);
	static Vector3D SquaredUniformDistribution_Oriented(const Vector3D& dir, float w, float h);
};


template<typename BP>
class ParticleEmitter;

//Si creo particleEmitter<>, es BetterParticle<ParticleEmitter<void>>
template<typename BP>
using CalculateIfParticleEmitterOrBP = std::conditional_t<std::is_void<BP>::value, ParticleEmitter<void>, BP>;

template<typename BP>
class ParticleEmitter : public BetterParticle<CalculateIfParticleEmitterOrBP<BP>>, public ParticleEmitterOperations
{
	friend class Scene;

protected:
	ParticleEmitter() {};
	ParticleEmitter(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :BetterParticle<BP>(renderItem, pos, v, a, deathCountdown, damping, w) {};
	ParticleEmitter(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :BetterParticle<BP>(pos, v, a, deathCountdown, damping, w) {};

};

class ParticleEmitter_Rectangular_Ortogonal : public ParticleEmitter<ParticleEmitter_Rectangular_Ortogonal>
{
	friend class Scene;
protected:
	ParticleEmitter_Rectangular_Ortogonal(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter<ParticleEmitter_Rectangular_Ortogonal>(renderItem, pos, v, a, deathCountdown, damping, w) {};
	ParticleEmitter_Rectangular_Ortogonal(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter<ParticleEmitter_Rectangular_Ortogonal>(pos, v, a, deathCountdown, damping, w) {};
public:
	template<typename T>
	void SetEmittingFunction(const Vector3D& dir, float w, float h, float pps, const BetterParticle<T>& p, ParticleSystem* mySystem) {
		double timeForNextParticle = deathCountdown;
		double timeBetweenParticles = 1 / pps;

		BetterParticleCopy<T> pc = p;
		SetExtraUpdateFunc([mySystem, timeForNextParticle, timeBetweenParticles, dir, w, h, pc](ParticleEmitter_Rectangular_Ortogonal* self, double dt) mutable
			{
				self->GenericEmittingFunctionCall(dir, timeForNextParticle, timeBetweenParticles, w, h, pc, mySystem);
			}
		);
	}
private:
	template<typename T>
	void GenericEmittingFunctionCall(const Vector3D& dir, double& timeForNextParticle, double timeBetweenParticles, float w, float h, const BetterParticle<T>& p, ParticleSystem* mySystem) {

		while (timeForNextParticle > deathCountdown) {
			timeForNextParticle -= timeBetweenParticles;

			BetterParticle<T>* particleReturned = mySystem->addParticle(p);

			if (particleReturned)
			{
				particleReturned->v.RotateVectorToDirPlane(dir);
				particleReturned->transform.p = SquaredUniformDistribution_Oriented(dir, w, h);
			}
		}
	}
};

//class ParticleEmitter_Conical : public ParticleEmitter
//{
//	friend class Scene;
//protected:
//	ParticleEmitter_Conical(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter(renderItem, pos, v, a, deathCountdown, damping, w) {};
//	ParticleEmitter_Conical(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter(pos, v, a, deathCountdown, damping, w) {};
//private:
//};



//class ParticleEmitter_Puntual : public ParticleEmitter
//{
//
//public:
//
//	ParticleEmitter_Puntual
//};