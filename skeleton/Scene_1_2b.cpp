#include "Scene_1_2b.h"

void Scene_1_2b::init()
{
}

void Scene_1_2b::keyPress(unsigned char key, const physx::PxTransform& cameraTransform)
{
	std::cout << key << '\n';
	switch (key) {
	case 'R': addProyectile(10, GetCamera()->getEye()+ 2*GetCamera()->getDir(), GetCamera()->getDir(), 450, 15, {0,-9.81,0}); break;
	case 'T': addProyectile(10, GetCamera()->getEye()+ 2 * GetCamera()->getDir(), GetCamera()->getDir(), 66, 15, { 0,-9.81,0 }); break;
	default:break;
	}
}