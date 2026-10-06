#include "Scene_1_2.h"

void Scene_1_2::init()
{
	this->sCamera = new Camera(physx::PxVec3(50.0f, 0, 0), physx::PxVec3(-1, 0, 0), true);
	this->addParticle(Vector3D(0, 0, 0));
}
