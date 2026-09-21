#include "Scene_0.h"

void Scene_0::init()
{
    Vector3D x = { 3,1,0 };
    Vector3D y = { 0,4,0 };
    Vector3D z = Vector3D::cross(x,y);

    x = x.normalize() * 5;
    y = y.normalize() * 5;
    z = z.normalize() * 5;

    m_transformX = physx::PxTransform(x);
    m_transformY = physx::PxTransform(y);
    m_transformZ = physx::PxTransform(z);
    m_transform0 = physx::PxTransform(Vector3D());

    // Ejemplo: Creación de una esfera usando las utilidades de render existentes
    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));


    // Se registra el RenderItem exactamente como en la plantilla original
    addRenderItem(shape, &m_transformX, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
    addRenderItem(shape, &m_transformY, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
    addRenderItem(shape, &m_transformZ, Vector4(0.0f, 0.0f, 1.0f, 1.0f));
    addRenderItem(shape, &m_transform0, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
}
