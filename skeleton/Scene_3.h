#pragma once
#include "Scene.h"
class Scene_3 :public Scene
{
    std::shared_ptr<ForceGenerator> wind;
    std::shared_ptr<ExplosionForceGenerator> explosion;
public:
    explicit Scene_3(std::string name) : Scene(std::move(name)),wind(nullptr),explosion(nullptr) { sCamera = new Camera({ -50,20,0 }, { 1,0,0 }); }

    void init() override;

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'R') {
            wind->setActive(!wind->getActive());
        }
        if (key == 'T') {
            explosion->explode();
        }
    }

    void cleanup() override {

    }
};


