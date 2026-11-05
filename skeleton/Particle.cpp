#include "Particle.h"

void Particle::SetRenderItem(const RenderItem* rip)
{
	if (renderItem) renderItem->release();
	renderItem = new RenderItemP(rip->shape, &transform, rip->color);
}

void Particle::SetRenderItemPrefab(const RenderItem* ri)
{
	if (renderItem) renderItem->release();
	renderItem = new RenderItemP(ri->shape, ri->color);
}

void Particle::SetRenderItemPrefab(const RenderItem_Prefab& ri)
{
	if (renderItem) renderItem->release();
	renderItem = new RenderItemP(ri.shape, ri.color);
}

void Particle::Integrate(double dt)
{
	(this->*integrateFunc)(dt);
}

Particle::Particle(const Particle& other) :
	transform(other.transform),
	v(other.v),
	a(Vector3D::Zero),
	p0(other.p0),
	w(other.w),
	damping(other.damping),
	hasStartedMoving(other.hasStartedMoving),
	integrateFunc(other.integrateFunc)
{
	if (other.renderItem != nullptr)
	{
			renderItem = new RenderItemP(other.renderItem->shape, &transform, other.renderItem->color);
	}
	else {
		renderItem = nullptr;
	}
};

Particle::Particle(const Vector3D& pos, const Vector3D& v,  double damping, double w, RenderItemP* renderItem, bool hasRenderItem) :transform(physx::PxTransform(pos)), v(v), a(Vector3D::Zero), damping(damping), hasStartedMoving(false), w(w), integrateFunc(&Particle::semiEulerIntegrate)
{
	if (hasRenderItem)
	{
		if (renderItem) 
		{
				this->renderItem = new RenderItemP(renderItem->shape, &transform, renderItem->color);
		}
		else
		{
			physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.5f));
			this->renderItem = new RenderItemP(shape, &transform, Vector4(0, 0, 0, 1));
		}
	}
	else {
		this->renderItem = nullptr;
	}
}
Particle::Particle(const Vector3D& pos, double damping, const Vector3D& v) : Particle(pos, v,  damping) {

}

Particle::Particle(double w, const Vector3D& pos, const Vector3D& v,  double damping) :Particle(pos, v, damping, w)
{
}

Particle& Particle::operator=(const Particle& other)
{
	if (this == &other)
		return *this;


	if (renderItem != nullptr)
		renderItem->release();

	if (other.renderItem != nullptr)
	{

			renderItem = new RenderItemP(other.renderItem->shape, &transform, other.renderItem->color);

	}
	else {
		renderItem = nullptr;
	}

	transform = other.transform;
	v = other.v;
	a =Vector3D::Zero;
	p0 = other.p0;
	w = other.w;
	damping = other.damping;
	hasStartedMoving = other.hasStartedMoving;
	integrateFunc = other.integrateFunc;

	return *this;
}

Particle::~Particle()
{
	if (renderItem != nullptr) { 
		renderItem->release(); 
		renderItem = nullptr; 
	}
}

void Particle::eulerIntegrate(double dt)
{

	p0 = transform.p;
	transform.p = transform.p + v * dt;
	v = (v + a * dt) * pow(damping, dt);
	hasStartedMoving = true;
}

void Particle::semiEulerIntegrate(double dt)
{
	p0 = transform.p;
	v = (v + a * dt) * pow(damping, dt);
	transform.p = transform.p + v * dt;
	hasStartedMoving = true;
}

void Particle::verletIntegrate(double dt)
{
	if (!hasStartedMoving) {
		semiEulerIntegrate(dt);
		hasStartedMoving = true;
	}
	else {
		const Vector3D ptemp = transform.p;
		transform.p = transform.p + (transform.p - p0) * pow(damping, dt) + a * pow(dt, 2);
		p0 = ptemp;
		v = (transform.p - p0) / (2 * dt);
	}
}
