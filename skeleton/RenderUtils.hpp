#ifndef __RENDER_UTILS_H__
#define __RENDER_UTILS_H__

#include "PxPhysicsAPI.h"
#include "core.hpp"
#include <memory>

class RenderItem;
void RegisterRenderItem(const RenderItem* _item);
void DeregisterRenderItem(const RenderItem* _item);
using TransformPointer = std::shared_ptr<physx::PxTransform>;

class RenderItem
{
	friend class Scene;

	private:
	RenderItem(physx::PxShape* _shape, TransformPointer _trans, const Vector4& _color) :
		shape(_shape), transform(_trans), actor(NULL), color(_color), references(1)
	{
		shape->acquireReference();
		RegisterRenderItem(this);
	}

	RenderItem(physx::PxShape* _shape, const Vector4& _color) :
		shape(_shape), transform(NULL), actor(NULL), color(_color), references(1)
	{
		shape->acquireReference();
		RegisterRenderItem(this);
	}

	RenderItem(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) :
		shape(_shape), transform(NULL), actor(_actor), color(_color), references(1)
	{
		shape->acquireReference();
		RegisterRenderItem(this);
	}

	RenderItem() : shape(NULL), transform(NULL), references(1) {}

	void addReference()
	{
		++references;
	}

	void release()
	{
		--references;
		if (references == 0)
		{
			DeregisterRenderItem(this);
			shape->release();
			delete this;
		}
	}
	
public:

	physx::PxShape* shape;
	TransformPointer transform;
	const physx::PxRigidActor* actor;
	Vector4 color;

	unsigned references;
};

double GetLastTime();
Camera* GetCamera();

physx::PxShape* CreateShape(const physx::PxGeometry& geo, const physx::PxMaterial* mat = nullptr);

#endif