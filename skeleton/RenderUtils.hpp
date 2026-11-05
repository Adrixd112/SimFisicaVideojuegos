#ifndef __RENDER_UTILS_H__
#define __RENDER_UTILS_H__

#include "PxPhysicsAPI.h"
#include "core.hpp"
#include <memory>
#include <type_traits>
#include<iostream>

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
	friend class Scene;
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

	RenderItem() : shape(NULL), actor(NULL), references(1) {}

	RenderItem(const RenderItem& other) : shape(other.shape), actor(other.actor), color(other.color), references(1)
	{
		//int i = 0;
	}

	virtual ~RenderItem() {
	} 

	void addReference()
	{
		++references;
	}

	virtual void release() {
		--references;
		if (references == 0)
		{
			delete this;
		}
	};

public:

	physx::PxShape* shape;
	const physx::PxRigidActor* actor;
	Vector4 color;

	unsigned references;
};

//para crear renderitems desde fuera de Scene y poder destruirlos
class RenderItem_Prefab : public RenderItem {
public:
	RenderItem_Prefab(physx::PxShape* _shape, const Vector4& _color) :RenderItem(_shape, _color) {}

	RenderItem_Prefab(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) :RenderItem(_shape, _actor, _color) {}

	RenderItem_Prefab() : RenderItem() {}

	RenderItem_Prefab(const RenderItem_Prefab& other) :RenderItem(other) {}

	virtual ~RenderItem_Prefab() {} //que se llame 2 veces al release no debería dar problemas porque la destructora solo se llama con release == 0;
};

class RenderItemP :public RenderItem
{
	friend class Particle;
	friend class Scene;
private:



	/*RenderItemP(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) : RenderItem(_shape, _actor, _color), transform(NULL) { RegisterRenderItem(this); }*/

	//Si no tiene transform, no lo registro en la lista de render.
	RenderItemP() : RenderItem(), transform(NULL) {}
	RenderItemP(physx::PxShape* _shape, physx::PxTransform* _trans, const Vector4& _color) : RenderItem(_shape, _color), transform(_trans) {
		if (transform != nullptr)RegisterRenderItem(this);
	}
	RenderItemP(const RenderItemP& other) :RenderItemP(other.shape, other.transform, other.color) {}
	RenderItemP(const RenderItem_Prefab& other) :RenderItem(other), transform(NULL)
	{
		//int i = 0;
	}
	RenderItemP(physx::PxShape* _shape, const Vector4& _color) : RenderItem(_shape, _color), transform(NULL) {}


	void release() override
	{
		--references;
		if (references == 0)
		{
			if (transform != nullptr)DeregisterRenderItem(this);
			delete this;
		}
	}
public:
	physx::PxTransform* GetTransform() const {
		return transform;
	}

	void SetTransform(physx::PxTransform* transformPointer) {

		if (transform == transformPointer)
			return;

		if (transform != nullptr) DeregisterRenderItem(this);

		transform = transformPointer;

		if (transform != nullptr) RegisterRenderItem(this);
		
	}
private:
	physx::PxTransform* transform;
};

//obsoleto pero posiblemente útil
class RenderItemO : public RenderItem
{
	friend class Scene;
private:

	RenderItemO(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) : RenderItem(_shape, _actor, _color), transform(NULL) { RegisterRenderItem(this); }
	//Si no tiene transform, no lo registro en la lista de render.
	RenderItemO() : RenderItem(), transform(NULL) {}
	RenderItemO(physx::PxShape* _shape, TransformSPointer _trans, const Vector4& _color) : RenderItem(_shape, _color), transform(_trans) {
		if (transform != nullptr)RegisterRenderItem(this);
	}
	RenderItemO(const RenderItemO& other) :RenderItemO(other.shape, other.transform, other.color) {}
	RenderItemO(physx::PxShape* _shape, const Vector4& _color) : RenderItem(_shape, _color), transform(NULL) {}
	RenderItemO(const RenderItem_Prefab& other) :RenderItem(other), transform(NULL) {}

	void release() override
	{
		--references;
		if (references == 0)
		{
			if (transform != nullptr)DeregisterRenderItem(this);
			shape->release();
			delete this;
		}
	}

public:
	TransformSPointer transform;
};


double GetLastTime();
Camera* GetCamera();
void SetCamera(Camera* camera);

physx::PxShape* CreateShape(const physx::PxGeometry& geo, const physx::PxMaterial* mat = nullptr);

#endif