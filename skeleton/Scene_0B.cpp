#include "Scene_0B.h"

void Scene_0B::init()
{
	const Vector3D v1 = { 2,0,3 };
	const Vector3D v2 = { -4,0,1 };
	const Vector3D v3= { 0,0,-5 };
	const Vector3D v4 = { 3,0,0 };


	float dot = Vector3D::dot(v1, Vector3D(0,0,1));
	m_transform1 = physx::PxTransform(v1);
	placeSphere(&m_transform1, dot);

	dot = Vector3D::dot(v2, Vector3D(0, 0, 1));
	m_transform2 = physx::PxTransform(v2);
	placeSphere(&m_transform2, dot);

	dot = Vector3D::dot(v3, Vector3D(0, 0, 1));
	m_transform3 = physx::PxTransform(v3);
	placeSphere(&m_transform3, dot);

	dot = Vector3D::dot(v4, Vector3D(0, 0, 1));
	m_transform4 = physx::PxTransform(v4);
	placeSphere(&m_transform4, dot);
}

void Scene_0B::placeSphere(physx::PxTransform* tr,float dot) {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

	if (dot > 0) {
		addRenderItem(shape, tr, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	}
	else if (dot < 0) {
		addRenderItem(shape, tr, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else {
		addRenderItem(shape, tr, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	}
}