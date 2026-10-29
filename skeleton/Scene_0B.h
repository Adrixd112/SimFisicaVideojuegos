#pragma once
#include "Scene.h"
class Scene_0B : public Scene
{
public:
	explicit Scene_0B(std::string name) : Scene(std::move(name)) {}

	void init() override;

	

	void update(double dt) override {
		// Lógica/Integración del alumno (por ejemplo, movimiento simple)
		//m_transform.p.y -= static_cast<float>(9.8 * dt);
	}

	void keyPress(unsigned char key, const physx::PxTransform& camera) override {

	}

	void cleanup() override {

	}
private:
	void placeSphere(const physx::PxTransform& tr, float dot);

	physx::PxTransform m_transform1;
	physx::PxTransform m_transform2;
	physx::PxTransform m_transform3;
	physx::PxTransform m_transform4;

};

