#include "Scene_1_2b.h"

void Scene_1_2b::init()
{
	addParticleSystem("1");

	GetParticleSystem("1")->addForceGenerator(std::make_shared<GravityForceGenerator>());
	GetParticleSystem("1")->addForceGenerator(std::make_shared<WindForceGenerator>());
}

void Scene_1_2b::keyPress(unsigned char key, const physx::PxTransform& cameraTransform)
{
	std::cout << key << '\n';
	switch (key) {
	case 'R': GetParticleSystem("1")->addParticle(GenerateProyectile(10, GetCamera()->getEye() + 2 * GetCamera()->getDir(), GetCamera()->getDir(), 450, 15,20)); break;
	case 'T': GetParticleSystem("1")->addParticle(GenerateProyectile(10, GetCamera()->getEye()+ 2 * GetCamera()->getDir(), GetCamera()->getDir(), 66, 15,20)); break;
	default:break;
	}
}