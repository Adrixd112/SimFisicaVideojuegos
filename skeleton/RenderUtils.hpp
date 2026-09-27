#ifndef __RENDER_UTILS_H__
#define __RENDER_UTILS_H__

#include "PxPhysicsAPI.h"
#include "core.hpp"
#include <memory>

class RenderItem;
void RegisterRenderItem(const RenderItem* _item);
void DeregisterRenderItem(const RenderItem* _item);
using TransformSPointer = std::shared_ptr<physx::PxTransform>;

class RenderItem
{

protected:
	RenderItem(physx::PxShape* _shape, const Vector4& _color) :
		shape(_shape), actor(NULL), color(_color), references(1)
	{
		shape->acquireReference();
		RegisterRenderItem(this);
	}

	RenderItem(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) :
		shape(_shape), actor(_actor), color(_color), references(1)
	{
		shape->acquireReference();
		RegisterRenderItem(this);
	}

	RenderItem() : shape(NULL), references(1) {}

	virtual ~RenderItem() {}

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
	const physx::PxRigidActor* actor;
	Vector4 color;

	unsigned references;
};

class RenderItemP:public RenderItem
{
	friend class Particle;
private:

	RenderItemP(physx::PxShape* _shape, physx::PxTransform* _trans, const Vector4& _color) : RenderItem(_shape,_color), transform(_trans) {}

	RenderItemP(physx::PxShape* _shape,  const Vector4& _color) : RenderItem(_shape, _color), transform(NULL) {}

	RenderItemP(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color): RenderItem(_shape,_actor,_color), transform(NULL) {}

	RenderItemP() : RenderItem(), transform(NULL) {}
public:
	physx::PxTransform* transform;
};

class RenderItemO : public RenderItem
{
	friend class Scene;
private:
	RenderItemO(physx::PxShape* _shape, TransformSPointer _trans, const Vector4& _color) : RenderItem(_shape, _color), transform(_trans) {}

	RenderItemO(physx::PxShape* _shape, const Vector4& _color) : RenderItem(_shape, _color), transform(NULL) {}

	RenderItemO(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) : RenderItem(_shape, _actor, _color), transform(NULL) {}

	RenderItemO() : RenderItem(), transform(NULL) {}

	public:
	std::shared_ptr<physx::PxTransform> transform;
};

double GetLastTime();
Camera* GetCamera();

physx::PxShape* CreateShape(const physx::PxGeometry& geo, const physx::PxMaterial* mat = nullptr);

#endif