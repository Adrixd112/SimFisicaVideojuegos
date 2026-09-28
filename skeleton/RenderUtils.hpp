#ifndef __RENDER_UTILS_H__
#define __RENDER_UTILS_H__

#include "PxPhysicsAPI.h"
#include "core.hpp"
#include <memory>
#include <type_traits>

class RenderItemO;
class RenderItemP;

class RenderItem;
void RegisterRenderItem(const RenderItemO* _item);
void DeregisterRenderItem(const RenderItemO* _item);
void RegisterRenderItem(const RenderItemP* _item);
void DeregisterRenderItem(const RenderItemP* _item);





using TransformSPointer = std::shared_ptr<physx::PxTransform>;

class RenderItem
{

protected:
	RenderItem(physx::PxShape* _shape, const Vector4& _color) :
		shape(_shape), actor(NULL), color(_color), references(1)
	{
		shape->acquireReference();
	}

	RenderItem(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) :
		shape(_shape), actor(_actor), color(_color), references(1)
	{
		shape->acquireReference();
	}

	RenderItem() : shape(NULL), references(1) {}

	virtual ~RenderItem() {}

	void addReference()
	{
		++references;
	}

	virtual void release() = 0;
	
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

	RenderItemP(physx::PxShape* _shape, physx::PxTransform* _trans, const Vector4& _color) : RenderItem(_shape,_color), transform(_trans) { RegisterRenderItem(this); }

	RenderItemP(physx::PxShape* _shape,  const Vector4& _color) : RenderItem(_shape, _color), transform(NULL) { RegisterRenderItem(this); }

	RenderItemP(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color): RenderItem(_shape,_actor,_color), transform(NULL) { RegisterRenderItem(this); }

	RenderItemP() : RenderItem(), transform(NULL) { RegisterRenderItem(this); }

	void release() override
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
	physx::PxTransform* transform;
};

class RenderItemO : public RenderItem
{
	friend class Scene;
private:
	RenderItemO(physx::PxShape* _shape, TransformSPointer _trans, const Vector4& _color) : RenderItem(_shape, _color), transform(_trans) { RegisterRenderItem(this); }

	RenderItemO(physx::PxShape* _shape, const Vector4& _color) : RenderItem(_shape, _color), transform(NULL) { RegisterRenderItem(this); }

	RenderItemO(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) : RenderItem(_shape, _actor, _color), transform(NULL) { RegisterRenderItem(this); }

	RenderItemO() : RenderItem(), transform(NULL) { RegisterRenderItem(this); }

	void release() override
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
	std::shared_ptr<physx::PxTransform> transform;
};

double GetLastTime();
Camera* GetCamera();

physx::PxShape* CreateShape(const physx::PxGeometry& geo, const physx::PxMaterial* mat = nullptr);

#endif