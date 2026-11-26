#include "Scene_1_2b.h"
#include "RenderUtils.hpp"
#include "BetterParticle.h"
void Scene_1_2b::init()
{
	addParticleSystem("1");
	addParticleSystem("nograv");
	std::cout << "esta" << std::endl;
	GetParticleSystem("1")->addForceGenerator(std::make_shared<GravityForceGenerator>());
	GetParticleSystem("1")->addForceGenerator(std::make_shared<WindForceGenerator>());
}

void Scene_1_2b::keyPress(unsigned char key, const physx::PxTransform& cameraTransform)
{
	std::cout << key << '\n';
	switch (key) {
	case 'R': { 
		Particle_Prefab<Proyectile> proy = GenerateProyectile(10, GetCamera()->getEye() + 2 * GetCamera()->getDir(), GetCamera()->getDir(), 450, 15, 20);
		RenderItem_Prefab ripParticulaAzul(CreateShape(physx::PxSphereGeometry(0.5)), Vector4(0.3, 0.3, 1, 1));
		GenerateBetterParticlePrefab<BetterParticle<>>(ripParticulaAzul,100);

		proy.SetExtraUpdateFunc();
		GetParticleSystem("1")->addParticle(proy); break; 
	}
	case 'T': GetParticleSystem("1")->addParticle(GenerateProyectile(10, GetCamera()->getEye()+ 2 * GetCamera()->getDir(), GetCamera()->getDir(), 66, 15,20)); break;
	default:break;
	}
}