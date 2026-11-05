#pragma once
#include "Scene.h"
class Scene_3B :public Scene
{
private:
    std::shared_ptr<ExplosionForceGenerator> explosion;
public:
    explicit Scene_3B(std::string name) : Scene(std::move(name)),explosion(nullptr) { sCamera = new Camera({ -100,20,0 }, { 1,0,0 }); }

    void init() override;

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        switch (key) {
        case 'R': GetParticleSystem("1")->setUseForcesActive(!GetParticleSystem("1")->getUseForcesActive()); break;
        case 'T': GetParticleSystem("2")->setUseForcesActive(!GetParticleSystem("2")->getUseForcesActive()); break;
        case 'Y': explosion->explode();
        }
    }

    void cleanup() override {

    }
};

