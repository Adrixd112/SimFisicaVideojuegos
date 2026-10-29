#pragma once
#include "BetterParticle.h"
#include <random>
class ParticleEmitter : public BetterParticle
{
	static std::mt19937 generator;
	static std::uniform_real_distribution<float> uDistribution;
	static std::normal_distribution<float> nDistribution;

	ParticleSystem* mySystem;
public:
	ParticleEmitter() {};
	ParticleEmitter(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1):BetterParticle (renderItem, pos, v , a ,deathCountdown ,  damping ,  w) {};
	ParticleEmitter(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :BetterParticle(pos, v, a, deathCountdown, damping, w) {};

	static float UniformDistribution(float a, float b);
	static float NormalDistribution(float mean, float sigma);
	static Vector2D NormalBidimensionalDistribution( float sigma);
	static Vector2D CircularUniformDistribution( float radius);
	static Vector2D SquaredUniformDistribution(const Vector2D& firstCorner, const Vector2D& oppositeCorner);

	static Vector3D NormalBidimensionalDistribution_Oriented(const Vector3D& origin, const Vector3D& dir, float sigma);
	static Vector3D CircularUniformDistribution_Oriented(const Vector3D& origin, const Vector3D& dir, float radius);
	static Vector3D SquaredUniformDistribution_Oriented(const Vector3D& origin, const Vector3D& dir, float w, float h);

private:
	static Vector3D RotateVectorToDirPlane(const Vector3D& origin, const Vector3D& dir, const Vector2D& planeCoordinates);
};

class ParticleEmitter_Rectangular_Ortogonal : public ParticleEmitter
{

public:
	ParticleEmitter_Rectangular_Ortogonal(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter(renderItem, pos, v, a, deathCountdown, damping, w) {};
	ParticleEmitter_Rectangular_Ortogonal(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter(pos, v, a, deathCountdown, damping, w) {};
private:
	void SetEmittingFunction(const Vector3D& dir , float w, float h, float pps, BetterParticle* p) {
		double timeForNextParticle = 0;
		double stepBetweenParticles = 0;
		extraUpdateFunc = [this,timeForNextParticle,stepBetweenParticles](double dt) mutable
			{
				while (timeForNextParticle > deathCountdown) {
					timeForNextParticle -= stepBetweenParticles;

				}
				SquaredUniformDistribution_Oriented
			};
	}
};

class ParticleEmitter_Conical : public ParticleEmitter
{

public:
	ParticleEmitter_Conical(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter(renderItem, pos, v, a, deathCountdown, damping, w) {};
	ParticleEmitter_Conical(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :ParticleEmitter(pos, v, a, deathCountdown, damping, w) {};
private:
	Generate
};



class ParticleEmitter_Puntual : public ParticleEmitter
{

public:

	ParticleEmitter_Puntual
};