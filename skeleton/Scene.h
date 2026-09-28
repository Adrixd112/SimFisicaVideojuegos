#pragma once

#include <string>
#include <vector>
#include "PxPhysicsAPI.h"
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <unordered_set>
#include <memory>
#include <iostream>
// Clase base para las distintas escenas de la aplicación.
// Provee la interfaz mínima que debe implementar cualquier escena:
// inicialización, limpieza, actualización por frame y manejo de teclado.
class Scene
{
public:
	// Construye la escena con un nombre identificador.
	explicit Scene(std::string name) : m_name(std::move(name)) {}
	virtual ~Scene() = default;

	// Inicializa recursos de la escena (físicos, gráficos, datos, ...).
	virtual void init() = 0;

	// Libera los recursos asignados en init().
	//Invariantes: el todo renderItem existente debe estar en la lista de la escena y todo renderItem de la lista de la escena existe.
	virtual void cleanup() {
		for (RenderItemO* ri : nonParticleRenderItems) {
			ri->release();
		}
		nonParticleRenderItems.clear();
		for (Particle* p : particles) {
			delete p;
		}
		particles.clear();
	}
	RenderItemO* addRenderItem(physx::PxShape* _shape, const Vector3& _pos, const physx::PxQuat& quat, const Vector4& _color)
	{
		nonParticleTransforms.push_back(std::make_shared<physx::PxTransform>(_pos,quat));
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
	//Invariantes: el todo renderItem existente debe estar en una partícula o en la lista de la escena y todo renderItem de la lista de la escena existe.
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
	void physicsUpdate(double dt) { for (Particle* p : particles) { p->Integrate(dt); } }
	// Manejo de pulsación de tecla.
	// Se recibe la tecla pulsada y la transformada de la cámara para
	// permitir respuestas dependientes de la orientación/posición de la cámara.
	// Método opcional que puede ser sobrescrito por escenas que lo necesiten.
	virtual void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {}

	// Devuelve el nombre identificador de la escena.
	[[nodiscard]] const std::string& getName() const { return m_name; }

protected:
	// Nombre de la escena (útil para identificarla en menús o logs).
	std::string m_name;
private:
	std::unordered_set<RenderItemO*> nonParticleRenderItems;
	std::vector<TransformSPointer> nonParticleTransforms;
	std::vector<Particle*> particles;
};
