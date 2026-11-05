#pragma once

#include <string>
#include <vector>
#include <limits>
#include "PxPhysicsAPI.h"
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "Particle.h"
#include "Proyectile.h"
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "ParticleSystem.h"

#include "ForceGenerator.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"

// Clase base para las distintas escenas de la aplicación.
// Provee la interfaz mínima que debe implementar cualquier escena:
// inicialización, limpieza, actualización por frame y manejo de teclado.
class Scene
{
public:
	// Construye la escena con un nombre identificador.
	explicit Scene(std::string name) : m_name(std::move(name)), sCamera(nullptr) { paused = false; }
	virtual ~Scene() = default;

	// Inicializa recursos de la escena (físicos, gráficos, datos, ...).
	virtual void init() = 0;

	// Libera los recursos asignados en init().
	//Invariantes: el todo renderItem existente debe estar en la lista de la escena y todo renderItem de la lista de la escena existe.
	void cleanupSceneParent() {
		for (RenderItemO* ri : nonParticleRenderItems) {
			ri->release();
		}
		nonParticleRenderItems.clear();
		for (Particle* p : particles) {
			delete p;
		}
		particles.clear();
		particleSystems.clear();
	}
	virtual void cleanup() {}
	RenderItemO* addRenderItem(physx::PxShape* _shape, const Vector3& _pos, const physx::PxQuat& quat, const Vector4& _color)
	{
		nonParticleTransforms.push_back(std::make_shared<physx::PxTransform>(_pos, quat));
		RenderItemO* ri = new RenderItemO(_shape, *--nonParticleTransforms.end(), _color);
		nonParticleRenderItems.insert(ri);
		return ri;
	}
	RenderItemO* addRenderItem(physx::PxShape* _shape, const Vector3& _pos, const Vector4& _color)
	{
		nonParticleTransforms.push_back(std::make_shared<physx::PxTransform>(_pos));
		RenderItemO* ri = new RenderItemO(_shape, *--nonParticleTransforms.end(), _color);
		nonParticleRenderItems.insert(ri);
		return ri;
	}
	RenderItemO* addRenderItem(physx::PxShape* _shape, const physx::PxTransform& _trans, const Vector4& _color)
	{
		nonParticleTransforms.push_back(std::make_shared<physx::PxTransform>(_trans));
		RenderItemO* ri = new RenderItemO(_shape, *--nonParticleTransforms.end(), _color);
		nonParticleRenderItems.insert(ri);
		return ri;
	}
	RenderItemO* addRenderItem(physx::PxShape* _shape, TransformSPointer _trans, const Vector4& _color) {
		RenderItemO* ri = new RenderItemO(_shape, _trans, _color);
		nonParticleRenderItems.insert(ri);
		return ri;
	}
	RenderItemO* addRenderItem(physx::PxShape* _shape, const Vector4& _color) {
		RenderItemO* ri = new RenderItemO(_shape, _color);
		nonParticleRenderItems.insert(ri);
		return ri;
	}
	RenderItemO* addRenderItem(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) {
		RenderItemO* ri = new RenderItemO(_shape, _actor, _color);
		nonParticleRenderItems.insert(ri);
		return ri;
	}
	RenderItemO* addRenderItem() {
		RenderItemO* ri = new RenderItemO();
		nonParticleRenderItems.insert(ri);
		return ri;
	}

	Particle* addParticle(const Vector3D& pos, const Vector3D& v = Vector3D::Zero,  double damping = 0.97) {
		particles.push_back(new Particle(pos, v,  damping));
		return particles.back();
	}
	Particle* addParticle(const Vector3D& pos, double damping, const Vector3D& v = Vector3D::Zero) {
		particles.push_back(new Particle(pos, v,  damping));
		return particles.back();
	}

	Proyectile* addProyectile(const Vector3D& pos, double vRealProp, const Vector3D& v = Vector3D::Zero,  double damping = 0.97, double w = 1) {
		Proyectile* p = new Proyectile(pos, vRealProp, v,  damping, w);
		particles.push_back(p);
		return p;
	}
	Proyectile* addProyectile(double m, const Vector3D& pos, const Vector3D& dirV, double vReal, double vSim, double damping = 0.97) {
		Proyectile* p = new Proyectile(m, pos, dirV, vReal, vSim, damping);
		particles.push_back(p);
		return p;
	}
	/*Proyectile* addProyectile(const Vector3D& pos, double damping, double vRealProp, const Vector3D& v = Vector3D::Zero, const Vector3D& a = Vector3D::Zero)
	{
		Proyectile* p = new Proyectile(pos, vRealProp, v,  damping);
		particles.push_back(p);
		return p;
	}
	Proyectile* addProyectile(double w, const Vector3D& pos, double vRealProp, const Vector3D& v = Vector3D::Zero,  double damping = 0.97)
	{
		Proyectile* p = new Proyectile(pos, vRealProp, v,  damping, w);
		particles.push_back(p);
		return p;
	}*/

	//Proyectile* addProyectile(double m, const Vector3D& pos, const Vector3D& v = Vector3D::Zero, double vReal = 10,  double damping = 0.97) {
	//	Proyectile* p = new Proyectile(m, pos, v, vReal,  damping);
	//	particles.push_back(p);
	//	return p;
	//}


	bool addParticleSystem(std::string name) {
		if (particleSystems.find(name) != particleSystems.end())
		{
			std::cout << "------WARNING: El particleSystem \"" << name << "\" YA existe------\n";
			return false;
		}
		particleSystems[name];
	}

	ParticleSystem* GetParticleSystem(std::string name) {
		if (particleSystems.find(name) == particleSystems.end())
		{
			std::cout << "------WARNING: El particleSystem \"" << name << "\" NO existe------\n";
			return nullptr;
		}

		return &particleSystems[name];
	}


	//antiguos

	template <typename BP>
	Particle_Prefab<BP> GenerateBetterParticlePrefab(const Vector3D& pos = Vector3D::Zero, const Vector3D& v = Vector3D::Zero,  float deathCountdown = -1, double damping = 0.97, double m = 1) {
		double w = 1 / m;
		BP bp = BP(pos, v,  deathCountdown, damping, w);
		return bp;
	}

	template <typename BP>
	Particle_Prefab<BP> GenerateBetterParticlePrefab(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = Vector3D::Zero,  float deathCountdown = -1, double damping = 0.97, double m = 1) {
		double w = 1 / m;
		BP bp = BP(renderItem, pos, v,  deathCountdown, damping, w);
		return bp;
	}

	template <typename BP>
	Particle_Prefab<BP> GenerateBetterParticlePrefab(const RenderItem_Prefab& renderItemPrefab, const Vector3D& pos, const Vector3D& v = Vector3D::Zero,  float deathCountdown = -1, double damping = 0.97, double m = 1) {
		double w = 1 / m;
		RenderItemP* ripp= new RenderItemP(renderItemPrefab);
		BP p = BP(ripp, pos, v,  deathCountdown, damping, w);
		return p;
	}



	//eficientes al escribir

	template <typename BP>
	Particle_Prefab<BP> GenerateBetterParticlePrefab(float deathCountdown = -1, double m = 1, double damping = 0.97) {
		double w = 1 / m;
		BP bp = BP(Vector3D::Zero, Vector3D::Zero, deathCountdown, damping, w);
		return bp;
	}

	template <typename BP>
	Particle_Prefab<BP> GenerateBetterParticlePrefab(const RenderItemP* renderItemPrefab, float deathCountdown = -1, double m = 1, double damping = 0.97) {
		double w = 1 / m;
		BP p = BP(ripp, Vector3D::Zero, Vector3D::Zero, deathCountdown, damping, w);
		return p;
	}

	template <typename BP>
	Particle_Prefab<BP> GenerateBetterParticlePrefab(const RenderItem_Prefab& renderItemPrefab, float deathCountdown = -1, double m = 1, double damping = 0.97) {
		double w = 1 / m;
		RenderItemP* ripp = new RenderItemP(renderItemPrefab);
		BP p = BP(ripp, Vector3D::Zero, Vector3D::Zero ,deathCountdown, damping, w);
		return p;
	}

	//Invariantes: todo renderItem existente debe estar en una partícula o en la lista de la escena y todo renderItem de la lista de la escena existe.
	bool removeRenderItem(RenderItemO*& ri) {
		bool found = nonParticleRenderItems.erase(ri); //devuelve int n elems borrados que solo pueden ser 0->false o 1->true
		if (found)
		{
			ri->release(); // Deregistra y destruye el item
			ri = nullptr;
		}
		return found;
	}
	// Actualiza la lógica de la escena.
	// dt: tiempo en segundos transcurrido desde la última actualización.
	virtual void update(double dt) {};
	void physicsUpdate(double dt) {
		if (!paused)
		{
			for (Particle* p : particles) { p->Integrate(dt); }
			for (std::pair<const std::string, ParticleSystem>& ps : particleSystems) {
				ps.second.updateParticles(dt);
			}
		}

	}
	// Manejo de pulsación de tecla.
	// Se recibe la tecla pulsada y la transformada de la cámara para
	// permitir respuestas dependientes de la orientación/posición de la cámara.
	// Método opcional que puede ser sobrescrito por escenas que lo necesiten.
	virtual void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {};

	void keyPressSceneParent(unsigned char key, const physx::PxTransform& cameraTransform)
	{
		switch (key) {
		case ' ':paused = !paused;break;
		default:break;
		}
	}

	// Devuelve el nombre identificador de la escena.
	[[nodiscard]] const std::string& getName() const { return m_name; }


	Camera* getSceneCamera() const { return sCamera; };


protected:
	// Nombre de la escena (útil para identificarla en menús o logs).
	std::string m_name;
	Camera* sCamera;
	bool paused;
private:

	std::unordered_map<std::string, ParticleSystem> particleSystems;
	std::unordered_set<RenderItemO*> nonParticleRenderItems;
	std::vector<TransformSPointer> nonParticleTransforms;
	std::vector<Particle*> particles;
};
