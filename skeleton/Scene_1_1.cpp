#include "Scene_1_1.h"

void Scene_1_1::init()
{
	addParticle(Vector3D(0, 0, 0), Vector3D(3, 0, 0), Vector3D(0.1, 0, 0));

	Particle* verletP = addParticle(Vector3D(0, 0, 0), Vector3D(3, 0, 0), Vector3D(0.1, 0, 0));
	verletP->renderItem->color = Vector4(1, 1, 0, 1);
	verletP->setIntegrateVerlet();

}
