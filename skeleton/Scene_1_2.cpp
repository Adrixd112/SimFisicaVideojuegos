#include "Scene_1_2.h"

void Scene_1_2::init()
{
	this->sCamera = new Camera(physx::PxVec3(-50.0f, 0, 0), physx::PxVec3(1, 0, 0), true,0.05);
	this->addParticle(Vector3D(0, 0, 0), Vector3D(0,0,10),{0,-9.81,0});
	this->addProyectile(Vector3D(0, 0, 0),0.7, Vector3D(0, 0, 10), { 0,-9.81,0 });
	paused = true;
}

void Scene_1_2::keyPress(unsigned char key, const physx::PxTransform& cameraTransform)
{
	//std::cout << key<<'\n';
	switch (key) {
	case 'R': addProyectile(10,Vector3D(0, 0, 0),{0,10,10},450,15, { 0,-9.81,0 }); break;
	default:break;
	}
}
