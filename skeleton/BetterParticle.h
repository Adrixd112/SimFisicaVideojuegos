#pragma once
#include "Particle.h"
#include <functional>
#include <utility>
#include <type_traits>



//Posible mejora: hacer que todos los iguales utilicen un único renderIrem o algo así
//Usar funciones con nombre si
class GenericBetterParticle :public Particle {
	friend class Scene;
	friend class ParticleSystem;
private:
	bool alive;

protected:
	float deathCountdown;
	bool hasLifetime;

protected:
	GenericBetterParticle() :Particle(), alive(false) {};

	GenericBetterParticle(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : 
		Particle(pos, v, a, damping, w, renderItem, renderItem),
		alive(true),
		deathCountdown(deathCountdown),
		hasLifetime(deathCountdown >= 0) 
	{
	};
	GenericBetterParticle(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) : 
		Particle(pos, v, a, damping, w, nullptr, true),
		alive(true),
		deathCountdown(deathCountdown),
		hasLifetime(deathCountdown >= 0) 
	{
	};

	GenericBetterParticle(const GenericBetterParticle& other) :
		Particle(),
		alive(other.alive),
		deathCountdown(other.deathCountdown),
		hasLifetime(other.hasLifetime)
	{
	};

public:
	bool GetAlive() { return alive; }
	void SetAlive(bool alive) { this->alive = alive; }
	float GetDeathCountdown() { return deathCountdown; }
	float SetDeathCountdown(float count) { this->deathCountdown = count; }

	virtual void Integrate(double dt) {};
};

template<typename BP = void >
class BetterParticle :public GenericBetterParticle
{
	friend class Scene;
	friend class ParticleSystem;
protected:
	//esta clase existe para poder eliminar betterParticle creadas con GenerateBetterParticlePrefab(...) desde las escenas.
	class BetterParticlePrefab;

private:

	//punteros a funciones que reciben la part�cula sobre la que se llamar� a la funci�n.
	std::function<void(BP*, double)> extraUpdateFunc;
	std::function<void(BP*)> onDeath;

	//will die if this returns true
	std::function<bool(BP*)> willDieConditions;
	std::function<bool(BP*)> isSleep;


protected:

	BetterParticle() :GenericBetterParticle() {};

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
	BetterParticle(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :
		GenericBetterParticle(renderItem, pos, v, a, deathCountdown, damping, w),
		extraUpdateFunc(nullptr),
		onDeath(nullptr),
		willDieConditions(nullptr),
		isSleep(nullptr)
	{
	}

	//le pone renderItem default
	BetterParticle(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) :
		GenericBetterParticle(pos, v, a, deathCountdown, damping, w),
		extraUpdateFunc(nullptr),
		onDeath(nullptr),
		willDieConditions(nullptr),
		isSleep(nullptr)
	{
	}

	BetterParticle(const BetterParticle<BP>& other) : 
		GenericBetterParticle(other),
		extraUpdateFunc(other.extraUpdateFunc),
		onDeath(other.onDeath),
		willDieConditions(other.willDieConditions),
		isSleep(other.isSleep)
	{
	}

	void Integrate(double dt) override {
		if (!isSleep(static_cast<BP*>(this)) || !isSleep(static_cast<BP*>(this)))
		{
			if (extraUpdateFunc) extraUpdateFunc(static_cast<BP*>(this), dt);

			Particle::Integrate(dt);

			deathCountdown -= dt;
			if (hasLifetime && deathCountdown <= 0) SetAlive(false);
		}

		if (willDieConditions) SetAlive(GetAlive() && !willDieConditions(static_cast<BP*>(this)));

		if (!GetAlive() && onDeath) onDeath(static_cast<BP*>(this));
	}

public:
	void SetExtraUpdateFunc(std::function<void(BP*, double)> func)
	{
		extraUpdateFunc = std::move(func);
	}

	void SetOnDeath(std::function<void(BP*)> func) {
		onDeath = std::move(func);
	}

	void SetWillDieConditions(std::function<bool(BP*)> func) {
		willDieConditions = std::move(func);
	}

	void SetIsSleep(std::function<bool(BP*)> func) {
		isSleep = std::move(func);
	}




};

template <typename BP>
class BetterParticlePrefab : public BetterParticle<BP> {
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

	BetterParticlePrefab(const BetterParticle<BP>& other) : BetterParticle(other)
	{
	}
public:
	~BetterParticlePrefab() {};
};


template<typename BP>
class ParticleEmitter;

template<typename BP>
struct NormalizeBetterParticle {
	using type = std::conditional_t<std::is_base_of<GenericBetterParticle, BP>::value, BP, void>;
};

template<>
struct NormalizeBetterParticle<BetterParticle<void>> {
	using type = BetterParticlePrefab<void>;
};

template<>
struct NormalizeBetterParticle <ParticleEmitter<void>> {
	using type = ParticleEmitter<void>;
};


template<typename BP>
using IsOrInheritsFromBetterParticle = std::enable_if_t<
	!std::is_void<typename NormalizeBetterParticle<BP>::type>::value,
	typename NormalizeBetterParticle<BP>::type
>;


