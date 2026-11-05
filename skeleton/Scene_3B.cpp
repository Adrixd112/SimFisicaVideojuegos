#include "Scene_3B.h"

void Scene_3B::init()
{
	addParticleSystem("1");

	//Rectangular-uniforme1

	RenderItem_Prefab rip(CreateShape(physx::PxSphereGeometry(1.0f)), Vector4(1, 0, 0, 1));

	Particle_Prefab<ParticleEmitter_Rectangular_Ortogonal> p = GenerateBetterParticlePrefab<ParticleEmitter_Rectangular_Ortogonal>(rip, -1, std::numeric_limits<double>::infinity());

	RenderItem_Prefab ripParticulaGris(CreateShape(physx::PxSphereGeometry(0.5f)), Vector4(0.4, 0.4, 0.4, 1));

	p.SetEmittingFunction(Vector3D(0, -1, 0).normalize(), 3, 20, 20, 100, GenerateBetterParticlePrefab<BetterParticle<>>(ripParticulaGris, 3), GetParticleSystem("1"));
	p.transform.p = { 0,100,0 };
	GetParticleSystem("1")->addParticle(p);

	//Rectangular-uniforme2

	addParticleSystem("2");
	Particle_Prefab<ParticleEmitter_Rectangular_Ortogonal> p2 = GenerateBetterParticlePrefab<ParticleEmitter_Rectangular_Ortogonal>(rip, -1, std::numeric_limits<double>::infinity());

	RenderItem_Prefab ripParticulaRoja(CreateShape(physx::PxSphereGeometry(0.5f)), Vector4(0.8, 0.8, 0.2, 1));

	p2.SetEmittingFunction(Vector3D(0, -1, 0).normalize(), 3, 20, 20, 100, GenerateBetterParticlePrefab<BetterParticle<>>(ripParticulaRoja, -1, 10), GetParticleSystem("2"));
	p2.transform.p = { 0,100,0 };

	GetParticleSystem("2")->addParticle(p2);





	//std::shared_ptr<ForceGenerator> gravity = std::make_shared<GravityForceGenerator> ();
	//std::shared_ptr<ForceGenerator> wind = std::shared_ptr<ForceGenerator>(new WindForceGenerator({ 0,0,1 }, 0, { 0,0,0 }, { 10000,10000,10000 }));
	//explosion = std::shared_ptr<ExplosionForceGenerator>(new ExplosionForceGenerator({0,0,0},1000,30));

	//GetParticleSystem("2")->addForceGenerator(explosion);
	//GetParticleSystem("1")->addForceGenerator(explosion);
	//GetParticleSystem("2")->addForceGenerator(wind);
	//GetParticleSystem("1")->addForceGenerator(wind);
	//GetParticleSystem("2")->addForceGenerator(gravity);
	//GetParticleSystem("1")->addForceGenerator(gravity);

}
