#pragma once
#include "Particle.h"
#include <functional>
#include <utility>
#include <type_traits>



//Posible mejora: hacer que todos los iguales utilicen un único renderIrem o algo así
//Usar funciones con nombre si

class BetterParticlePadre :public Particle
{
	friend class Scene;
	friend class ParticleSystem;
protected:
	//esta clase existe para poder eliminar betterParticle creadas con GenerateBetterParticlePrefab(...) desde las escenas.
	class BetterParticlePrefab;

private:
	bool alive;
protected:

	float deathCountdown;
	bool hasLifetime;

protected:

	BetterParticlePadre() :Particle(), alive(false) {};

	virtual ~BetterParticlePadre() = default;

	//BetterParticlePadre(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, double damping = 0.97, double w = 1, RenderItemP* renderItem = nullptr, std::function<void()> extraUpdateFunc = nullptr, std::function<void()> onDeath = nullptr, std::function<bool()> willDieConditions = nullptr, std::function<bool()> isSleep = nullptr, float deathCountdown = -1) : Particle(pos, v, a, damping, w,renderItem),
	//	alive(true),
	//	deathCountdown(deathCountdown),
	//	hasLifetime(deathCountdown >= 0),
	//	extraUpdateFunc(std::move(extraUpdateFunc)),
	//	onDeath(std::move(onDeath)),
	//	willDieConditions(std::move(willDieConditions)),
	//	isSleep(std::move(isSleep)) 
	//{}

	//Si le das renderItem, lo pone; si le dices nullptr, no lo pone.
	BetterParticlePadre(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : Particle(pos, v, a, damping, w, renderItem, renderItem),
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
	BetterParticlePadre(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : Particle(pos, v, a, damping, w, nullptr, true),
		alive(true),
		deathCountdown(deathCountdown),
		hasLifetime(deathCountdown >= 0),
		extraUpdateFunc(nullptr),
		onDeath(nullptr),
		willDieConditions(nullptr),
		isSleep(nullptr)
	{
	}

	BetterParticlePadre(const BetterParticlePadre& other) : Particle(other),
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

	virtual void setExtraUpdateFunc(std::function<void(BetterParticlePadre*, double)> func) = 0;

	virtual void setOnDeath(std::function<void(BetterParticlePadre*)> func) = 0;

	virtual void setWillDieConditions(std::function<bool(BetterParticlePadre*)> func) = 0;

	virtual void setIsSleep(std::function<bool(BetterParticlePadre*)> func) = 0;
	

	virtual void Integrate(double dt) = 0;
};

template<typename BP = BetterParticlePadre>
class BetterParticle :public Particle
{
	friend class Scene;
	friend class ParticleSystem;

protected:


	//punteros a funciones que reciben la partícula sobre la que se llamará a la función.
	std::function<void(BetterParticle<BP>*, double)> extraUpdateFunc;
	std::function<void(BetterParticle<BP>*)> onDeath;

	//will die if this returns true
	std::function<bool(BetterParticle<BP>*)> willDieConditions;
	std::function<bool(BetterParticle<BP>*)> isSleep;


protected:

	BetterParticlePadre() :Particle(), alive(false) {};

	virtual ~BetterParticlePadre() = default;

	//BetterParticlePadre(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, double damping = 0.97, double w = 1, RenderItemP* renderItem = nullptr, std::function<void()> extraUpdateFunc = nullptr, std::function<void()> onDeath = nullptr, std::function<bool()> willDieConditions = nullptr, std::function<bool()> isSleep = nullptr, float deathCountdown = -1) : Particle(pos, v, a, damping, w,renderItem),
	//	alive(true),
	//	deathCountdown(deathCountdown),
	//	hasLifetime(deathCountdown >= 0),
	//	extraUpdateFunc(std::move(extraUpdateFunc)),
	//	onDeath(std::move(onDeath)),
	//	willDieConditions(std::move(willDieConditions)),
	//	isSleep(std::move(isSleep)) 
	//{}

	BetterParticlePadre(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : Particle(pos, v, a, damping, w, renderItem, renderItem),
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
	BetterParticlePadre(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : Particle(pos, v, a, damping, w, nullptr, true),
		alive(true),
		deathCountdown(deathCountdown),
		hasLifetime(deathCountdown >= 0),
		extraUpdateFunc(nullptr),
		onDeath(nullptr),
		willDieConditions(nullptr),
		isSleep(nullptr)
	{
	}

	BetterParticle(const BetterParticle<BP>& other) : BetterParticlePadre(other),
		extraUpdateFunc(other.extraUpdateFunc),
		onDeath(other.onDeath),
		willDieConditions(other.willDieConditions),
		isSleep(other.isSleep)
	{
	}


public:
	void setExtraUpdateFunc(std::function<void(BetterParticle<BP>*, double)> func)
	{
		extraUpdateFunc = std::move(func);
	}

	void setOnDeath(std::function<void(BetterParticlePadre*)> func) {
		onDeath = std::move(func);
	}

	void setWillDieConditions(std::function<bool(BetterParticlePadre*)> func) {
		willDieConditions = std::move(func);
	}

	void setIsSleep(std::function<bool(BetterParticlePadre*)> func) {
		isSleep = std::move(func);
	}
	void Integrate(double dt) override {
		if (!isSleep || !isSleep(this))
		{
			if (extraUpdateFunc) extraUpdateFunc(this, dt);

			Particle::Integrate(dt);

			deathCountdown -= dt;
			if (hasLifetime && deathCountdown <= 0) alive = false;
		}

		if (willDieConditions) alive = alive && !willDieConditions(this);

		if (!alive && onDeath) onDeath(this);
	}
};


class BetterParticlePadre::BetterParticlePrefab : public BetterParticlePadre {
	friend class Scene;
private:
	BetterParticlePrefab(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : BetterParticlePadre(renderItem, pos, v, a, deathCountdown, damping, w)
	{
		int i = 0;
	}

	//le pone renderItem default
	BetterParticlePrefab(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : BetterParticlePadre(pos, v, a, deathCountdown, damping, w)
	{
		int i = 0;
	}

	BetterParticlePrefab(const BetterParticlePadre& other) : BetterParticlePadre(other)
	{
	}
public:
	~BetterParticlePrefab() {};
};

template<typename BP>
using IsOrInheritsFromBetterParticle = std::enable_if_t<
	std::is_base_of<BetterParticlePadre, BP>::value || std::is_same<BP, BetterParticlePadre>::value
	,
	typename std::conditional<
	std::is_same<BP, BetterParticlePadre>::value,
	BetterParticlePadre::BetterParticlePrefab,
	BP
	>::type
>;


