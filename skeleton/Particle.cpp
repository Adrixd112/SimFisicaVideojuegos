#include "Particle.h"

void Particle::Integrate(double dt)
{
	semiEulerIntegrate(dt);
}

Particle::Particle(const Vector3D& pos, const Vector3D& v , const Vector3D& a, double damping):v(v),a(a),damping(damping),hasStartedMoving(false),w(1)
{
	transform = physx::PxTransform(pos);
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.5f));
	renderItem = new RenderItemP(shape, &transform, Vector4(0, 0, 0, 1));
}
Particle::Particle(const Vector3D& pos, double damping, const Vector3D& v, const Vector3D& a): Particle(pos, v, a, damping) {
	
}

Particle::~Particle()
{
	if(renderItem!=nullptr)renderItem->release();
}

void Particle::eulerIntegrate(double dt)
{
	
	p0 = transform.p;
	transform.p = transform.p + v * dt;
	v = (v + a * dt) * pow(damping, dt);
}

void Particle::semiEulerIntegrate(double dt)
{
	p0 = transform.p;
	v = (v + a * dt)*pow(damping,dt);
	transform.p = transform.p + v * dt;
}

void Particle::verletIntegrate(double dt)
{
	if (!hasStartedMoving) {
		semiEulerIntegrate(dt);
		hasStartedMoving = true;
	}
	else {
		const Vector3D ptemp = transform.p;
		transform.p = 2 * transform.p - p0 + a * pow(dt, 2);
		p0 = ptemp;
		v = (transform.p - p0) / (2 * dt);
	}
}
