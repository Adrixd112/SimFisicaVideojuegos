#pragma once
#include "Scene.h"
class Scene_2 :public Scene
{
public:
    explicit Scene_2(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

    }

    void cleanup() override {

    }
};

