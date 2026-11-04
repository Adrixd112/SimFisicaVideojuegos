#pragma once

#include <string>
#include <vector>
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

	Particle* addParticle(const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, double damping = 0.97) {
		particles.push_back(new Particle(pos, v, a, damping));
		return particles.back();
	}
	Particle* addParticle(const Vector3D& pos, double damping, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }) {
		particles.push_back(new Particle(pos, v, a, damping));
		return particles.back();
	}

	Proyectile* addProyectile(const Vector3D& pos, double vRealProp, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, double damping = 0.97, double w = 1) {
		Proyectile* p = new Proyectile(pos, vRealProp, v, a, damping, w);
		particles.push_back(p);
		return p;
	}
	/*Proyectile* addProyectile(const Vector3D& pos, double damping, double vRealProp, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 })
	{
		Proyectile* p = new Proyectile(pos, vRealProp, v, a, damping);
		particles.push_back(p);
		return p;
	}
	Proyectile* addProyectile(double w, const Vector3D& pos, double vRealProp, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, double damping = 0.97)
	{
		Proyectile* p = new Proyectile(pos, vRealProp, v, a, damping, w);
		particles.push_back(p);
		return p;
	}*/

	Proyectile* addProyectile(double m, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, double vReal = 10, const Vector3D& a = { 0,0,0 }, double damping = 0.97) {
		Proyectile* p = new Proyectile(m, pos, v, vReal, a, damping);
		particles.push_back(p);
		return p;
	}
	Proyectile* addProyectile(double m, const Vector3D& pos, const Vector3D& dirV, double vReal, double vSim, const Vector3D& a = { 0,0,0 }, double damping = 0.97) {
		Proyectile* p = new Proyectile(m, pos, dirV, vReal, vSim, a, damping);
		particles.push_back(p);
		return p;
	}

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

	RenderItem_Prefab GenerateRenderItemPrefab(physx::PxShape* _shape, const Vector4& _color) {
		return RenderItem_Prefab(_shape, _color);
	}

	template <typename BP>
	BetterParticlePrefab<BP> GenerateBetterParticlePrefab(const Vector3D& pos = { 0,0,0 }, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) {
		BP bp = BP(pos, v, a, deathCountdown, damping, w);
		return BetterParticlePrefab<BP>(BP(pos, v, a, deathCountdown, damping, w));
	}

	template <typename BP>
	BetterParticlePrefab<BP> GenerateBetterParticlePrefab(RenderItemP* renderItem, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) {
		BP bp = BP(renderItem, pos, v, a, deathCountdown, damping, w);
		return BetterParticlePrefab<BP>(bp);
	}

	template <typename BP>
	BetterParticlePrefab<BP> GenerateBetterParticlePrefab(const RenderItem_Prefab& renderItemPrefab, const Vector3D& pos, const Vector3D& v = { 0,0,0 }, const Vector3D& a = { 0,0,0 }, float deathCountdown = -1, double damping = 0.97, double w = 1) {
		BP bp = BP(nullptr, pos, v, a, deathCountdown, damping, w);
		BetterParticlePrefab<BP> p(bp);
		std::string asa = typeid(p).name();
		p.Particle::SetRenderItem(renderItemPrefab);
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
