#include "Scene_1_1.h"

void Scene_1_1::init()
{
	Camera* cam = GetCamera();
	addParticle(Vector3D(0, 0, 0), Vector3D(3, 0, 0), Vector3D(0.1, 0, 0));

	Particle* verletP = addParticle(Vector3D(0, 0, 0), Vector3D(3, 0, 0), Vector3D(0.1, 0, 0));
	RenderItemP* t = verletP->renderItem;
	verletP->setIntegrateVerlet();

}
