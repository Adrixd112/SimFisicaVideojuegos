#include "Scene_0C.h"

void Scene_0C::init()
{
	const Vector3D p0 = Vector3D(-8, 1, -8);
	const Vector3D p1 = Vector3D(8,8,8);
	3 * p0;
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.5f));
	
	for (int i = 1;i <= steps;i++) 
	{
		float d = (float)i / (steps+1);
		addRenderItem(shape, p0+d*(p1-p0), Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	}
}
