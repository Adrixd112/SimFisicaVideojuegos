#pragma once
#include "BetterParticle.h"
#include "ParticleSystem.h"
#include <random>
class ParticleEmitter : public BetterParticlePadre
{
	friend class Scene;
private:
	static std::mt19937 generator;
	static std::uniform_real_distribution<float> uDistribution;
	static std::normal_distribution<float> nDistribution;

protected:
	class BetterParticleCopy : public BetterParticlePadre {
	public:
		BetterParticleCopy(const BetterParticlePadre& p) :BetterParticlePadre(p) {};
		BetterParticleCopy& operator=(const BetterParticlePadre& p) { BetterParticlePadre::operator=(p); }
	};

protected:
	ParticleEmitter() {};
	ParticleEmitter(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1):BetterParticlePadre (renderItem, pos, v , a ,deathCountdown ,  damping ,  w) {};
	ParticleEmitter(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :BetterParticlePadre(pos, v, a, deathCountdown, damping, w) {};

	static float UniformDistribution(float a, float b);
	static float NormalDistribution(float mean, float sigma);
	static Vector2D NormalBidimensionalDistribution( float sigma);
	static Vector2D CircularUniformDistribution( float radius);
	static Vector2D SquaredUniformDistribution(const Vector2D& firstCorner, const Vector2D& oppositeCorner);

	static Vector3D NormalBidimensionalDistribution_Oriented(const Vector3D& dir, float sigma);
	static Vector3D CircularUniformDistribution_Oriented( const Vector3D& dir, float radius);
	static Vector3D SquaredUniformDistribution_Oriented(const Vector3D& dir, float w, float h);

};

class ParticleEmitter_Rectangular_Ortogonal : public ParticleEmitter
{
	friend class Scene;
protected:
	ParticleEmitter_Rectangular_Ortogonal(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = {0,0,0}, const Vector3D& a = {0,0,0}, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter(renderItem, pos, v, a, deathCountdown, damping, w) {};
	ParticleEmitter_Rectangular_Ortogonal(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter(pos, v, a, deathCountdown, damping, w) {};
	void GenericEmittingFunctionCall(ParticleSystem* mySystem, double timeForNextParticle, double timeBetweenParticles, const Vector3D& dir, float w, float h, const BetterParticlePadre& p);
public:
	void SetEmittingFunction(const Vector3D& dir, float w, float h, float pps, const BetterParticlePadre& p, ParticleSystem* mySystem);
};

class ParticleEmitter_Conical : public ParticleEmitter
{
	friend class Scene;
protected:
	ParticleEmitter_Conical(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter(renderItem, pos, v, a, deathCountdown, damping, w) {};
	ParticleEmitter_Conical(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter(pos, v, a, deathCountdown, damping, w) {};
private:
};



//class ParticleEmitter_Puntual : public ParticleEmitter
//{
//
//public:
//
//	ParticleEmitter_Puntual
//};