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

	GenericBetterParticle(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = Vector3D::Zero,  float deathCountdown = -1, double damping = 0.97, double w = 1) : 
		Particle(pos, v,  damping, w, renderItem, renderItem),
		alive(true),
		deathCountdown(deathCountdown),
		hasLifetime(deathCountdown >= 0) 
	{
	};
	GenericBetterParticle(const Vector3D& pos, const Vector3D& v = Vector3D::Zero,  float deathCountdown = -1, double damping = 0.97, double w = 1) : 
		Particle(pos, v,  damping, w, nullptr, true),
		alive(true),
		deathCountdown(deathCountdown),
		hasLifetime(deathCountdown >= 0) 
	{
	};

	GenericBetterParticle(const GenericBetterParticle& other) :
		Particle(other),
		alive(other.alive),
		deathCountdown(other.deathCountdown),
		hasLifetime(other.hasLifetime)
	{
	};

	virtual void Integrate(double dt) {};
public:
	bool GetAlive() { return alive; }
	void SetAlive(bool alive) { this->alive = alive; }
	float GetDeathCountdown() { return deathCountdown; }
	float SetDeathCountdown(float count) { this->deathCountdown = count; }


};
template<typename BP = void >
class BetterParticle;

template<typename BP>
struct NormalizeBetterParticleImp {
	using type = BP;
};
template<>
struct NormalizeBetterParticleImp<void> {
	using type = BetterParticle<void>;
};

template<typename BP>
using NormalizeBetterParticle = typename NormalizeBetterParticleImp<BP>::type;

template<typename BP = void >
class BetterParticle :public GenericBetterParticle
{
	friend class Scene;
	friend class ParticleSystem;

private:

	//punteros a funciones que reciben la part�cula sobre la que se llamar� a la funci�n.
	std::function<void(NormalizeBetterParticle<BP>*, double)> extraUpdateFunc;
	std::function<void(NormalizeBetterParticle<BP>*)> onDeath;

	//will die if this returns true
	std::function<bool(NormalizeBetterParticle<BP>*)> willDieConditions;
	std::function<bool(NormalizeBetterParticle<BP>*)> isSleep;


protected:

	BetterParticle() :GenericBetterParticle() {};

	virtual ~BetterParticle() = default;

	//BetterParticle(const Vector3D& pos, const Vector3D& v = Vector3D::Zero,  double damping = 0.97, double w = 1, RenderItemP* renderItem = nullptr, std::function<void()> extraUpdateFunc = nullptr, std::function<void()> onDeath = nullptr, std::function<bool()> willDieConditions = nullptr, std::function<bool()> isSleep = nullptr, float deathCountdown = -1) : Particle(pos, v,  damping, w,renderItem),
	//	alive(true),
	//	deathCountdown(deathCountdown),
	//	hasLifetime(deathCountdown >= 0),
	//	extraUpdateFunc(std::move(extraUpdateFunc)),
	//	onDeath(std::move(onDeath)),
	//	willDieConditions(std::move(willDieConditions)),
	//	isSleep(std::move(isSleep)) 
	//{}

	//Si le das renderItem, lo pone; si le dices nullptr, no lo pone.
	BetterParticle(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = Vector3D::Zero,  float deathCountdown = -1, double damping = 0.97, double w = 1) :
		GenericBetterParticle(renderItem, pos, v,  deathCountdown, damping, w),
		extraUpdateFunc(nullptr),
		onDeath(nullptr),
		willDieConditions(nullptr),
		isSleep(nullptr)
	{
	}

	//le pone renderItem default
	BetterParticle(const Vector3D& pos, const Vector3D& v = Vector3D::Zero,  float deathCountdown = -1, double damping = 0.97, double w = 1) :
		GenericBetterParticle(pos, v,  deathCountdown, damping, w),
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

	virtual void Integrate(double dt) override {
		if (!isSleep || !isSleep(static_cast<NormalizeBetterParticle<BP>*>(this)))
		{
			if (extraUpdateFunc) extraUpdateFunc(static_cast<NormalizeBetterParticle<BP>*>(this), dt);

			Particle::Integrate(dt);

			deathCountdown -= dt;
			if (hasLifetime && deathCountdown <= 0) SetAlive(false);
		}

		if (willDieConditions) SetAlive(GetAlive() && !willDieConditions(static_cast<NormalizeBetterParticle<BP>*>(this)));

		if (!GetAlive() && onDeath) onDeath(static_cast<NormalizeBetterParticle<BP>*>(this));
	}

public:
	void SetExtraUpdateFunc(std::function<void(NormalizeBetterParticle<BP>*, double)> func)
	{
		extraUpdateFunc = std::move(func);
	}

	void SetOnDeath(std::function<void(NormalizeBetterParticle<BP>*)> func) {
		onDeath = std::move(func);
	}

	void SetWillDieConditions(std::function<bool(NormalizeBetterParticle<BP>*)> func) {
		willDieConditions = std::move(func);
	}

	void SetIsSleep(std::function<bool(NormalizeBetterParticle<BP>*)> func) {
		isSleep = std::move(func);
	}




};

//Clase segura que guarda una copia de una particle en cualquier lugar

template <typename BP>
class Particle_Prefab : public BP {
	static_assert(
		std::is_base_of<GenericBetterParticle, BP>::value,
		"BP must inherit from GenericBetterParticle"
		);

	friend class Scene;

public:

	Particle_Prefab(const BP& other) : BP(other)
	{
		if(this->Particle::renderItem!=nullptr) this->Particle::renderItem->SetTransform(nullptr);
	}
	Particle_Prefab(const Particle_Prefab<BP>& other) : BP(other)
	{
		if (this->Particle::renderItem != nullptr) this->Particle::renderItem->SetTransform(nullptr);
	}
	~Particle_Prefab() = default;
	
};





template<typename BP>
using IsOrInheritsFromBetterParticle = std::enable_if_t<
	std::is_base_of<GenericBetterParticle, BP>::value,
	BP
>;


