#pragma once
#include "Particle.h"
#include <functional>
#include <utility>


//Posible mejora: hacer que todos los iguales utilicen un único renderIrem o algo así
//Usar funciones con nombre si
class BetterParticle :public Particle
{
	friend class Scene;
	friend class ParticleSystem;

protected:
	bool alive;
	float deathCountdown;
	bool hasLifetime;

	std::function<void(double)> extraUpdateFunc;
	std::function<void()> onDeath;

	//will die if this returns true
	std::function<bool()> willDieConditions;
	std::function<bool()> isSleep;

	//esta clase existe para poder eliminar betterParticle creadas con GenerateBetterParticlePrefab(...) desde las escenas.
	class BetterParticlePrefab;

protected:

	BetterParticle() :Particle(), alive(false) {};

	virtual ~BetterParticle() = default;

	//BetterParticle(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, double damping = 0.97, double w = 1, RenderItemP* renderItem = nullptr, std::function<void()> extraUpdateFunc = nullptr, std::function<void()> onDeath = nullptr, std::function<bool()> willDieConditions = nullptr, std::function<bool()> isSleep = nullptr, float deathCountdown = -1) : Particle(pos, v, a, damping, w,renderItem),
	//	alive(true),
	//	deathCountdown(deathCountdown),
	//	hasLifetime(deathCountdown >= 0),
	//	extraUpdateFunc(std::move(extraUpdateFunc)),
	//	onDeath(std::move(onDeath)),
	//	willDieConditions(std::move(willDieConditions)),
	//	isSleep(std::move(isSleep)) 
	//{}

	//Si le das renderItem, lo pone; si le dices nullptr, no lo pone.
	BetterParticle(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : Particle(pos, v, a, damping, w, renderItem, renderItem),
		alive(true),
		deathCountdown(deathCountdown),
		hasLifetime(deathCountdown >= 0),
		extraUpdateFunc(nullptr),
		onDeath(nullptr),
		willDieConditions(nullptr),
		isSleep(nullptr)
	{
	}

	//le pone renderItem default
	BetterParticle(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : Particle(pos, v, a, damping, w, nullptr, true),
		alive(true),
		deathCountdown(deathCountdown),
		hasLifetime(deathCountdown >= 0),
		extraUpdateFunc(nullptr),
		onDeath(nullptr),
		willDieConditions(nullptr),
		isSleep(nullptr)
	{
	}

	BetterParticle(const BetterParticle& other) : Particle(other),
		alive(other.alive),
		deathCountdown(other.deathCountdown),
		hasLifetime(other.hasLifetime),
		extraUpdateFunc(other.extraUpdateFunc),
		onDeath(other.onDeath),
		willDieConditions(other.willDieConditions),
		isSleep(other.isSleep)
	{
	}


public:
	bool getAlive() { return alive; }
	bool setAlive(bool alive) { this->alive = alive; }
	float getDeathCountdown() { return deathCountdown; }
	float setDeathCountdown(float count) { this->deathCountdown = count; }

	void setExtraUpdateFunc(std::function<void(double)> func) {
		extraUpdateFunc = std::move(func);
	}

	void setOnDeath(std::function<void()> func) {
		onDeath = std::move(func);
	}

	void setWillDieConditions(std::function<bool()> func) {
		willDieConditions = std::move(func);
	}

	void setIsSleep(std::function<bool()> func) {
		isSleep = std::move(func);
	}

	void Integrate(double dt) override;



};

class BetterParticle::BetterParticlePrefab : public BetterParticle {
	friend class Scene;
private:
	BetterParticlePrefab(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : BetterParticle(renderItem, pos, v, a, deathCountdown, damping, w)
	{
		int i = 0;
	}

	//le pone renderItem default
	BetterParticlePrefab(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : BetterParticle(pos, v, a, deathCountdown, damping, w)
	{
		int i = 0;
	}

	BetterParticlePrefab(const BetterParticle& other) : BetterParticle(other)
	{
	}
public:
	~BetterParticlePrefab() {};
};
