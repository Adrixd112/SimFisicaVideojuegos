#pragma once
#include "Scene.h"
class Scene_0 :public Scene
{
public:
    explicit Scene_0(std::string name) : Scene(std::move(name)) {}

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
    physx::PxTransform m_transformX;
    physx::PxTransform m_transformY;
    physx::PxTransform m_transformZ;
    physx::PxTransform m_transform0;
};

