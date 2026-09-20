#pragma once

#include <string>
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include <unordered_set>
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
		for (RenderItem* ri : renderItems) {
				ri->release();
		}
	}

	RenderItem* addRenderItem(physx::PxShape* _shape, const physx::PxTransform* _trans, const Vector4& _color) {
		RenderItem* ri = new RenderItem(_shape, _trans, _color);
		renderItems.insert(ri);
	}
	RenderItem* addRenderItem(physx::PxShape* _shape, const Vector4& _color) {
		RenderItem* ri = new RenderItem(_shape, _color);
		renderItems.insert(ri);
	}
	RenderItem* addRenderItem(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) {
		RenderItem* ri = new RenderItem(_shape, _actor, _color);
		renderItems.insert(ri);
	}
	RenderItem* addRenderItem() {
		RenderItem* ri = new RenderItem();
		renderItems.insert(ri);
	}

	//Invariantes: el todo renderItem existente debe estar en la lista de la escena y todo renderItem de la lista de la escena existe.
	bool removeRenderItem(RenderItem*& ri) {
		bool found = renderItems.erase(ri); //devuelve int n elems borrados que solo pueden ser 0->false o 1->true
		if (found)
		{
			ri->release(); // Deregistra y destruye el item
			ri = nullptr;
		}
		return found;
	}
	// Actualiza la lógica de la escena.
	// dt: tiempo en segundos transcurrido desde la última actualización.
	virtual void update(double dt) = 0;

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
	std::unordered_set<RenderItem*> renderItems;
};
