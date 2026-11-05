#include "Scene_2.h"

void Scene_2::init()
{
	addParticleSystem("1");

	//Rectangular-uniforme

	RenderItem_Prefab rip(CreateShape(physx::PxSphereGeometry(1.0f)), Vector4(1, 0, 0, 1));

	Particle_Prefab<ParticleEmitter_Rectangular_Ortogonal> p = GenerateBetterParticlePrefab<ParticleEmitter_Rectangular_Ortogonal>(rip,20);

	RenderItem_Prefab ripParticulaGris(CreateShape(physx::PxSphereGeometry(1.0f)), Vector4(0.4, 0.4, 0.4, 1));

	p.SetEmittingFunction(Vector3D(0,1,1).normalize(), 1, 20, 20, 100, GenerateBetterParticlePrefab<BetterParticle<>>(ripParticulaGris, 10.0f), GetParticleSystem("1"));

	GetParticleSystem("1")->addParticle(p);

	//Cónica-orientada-uniforme

	Particle_Prefab<ParticleEmitter_Conical> pc = GenerateBetterParticlePrefab<ParticleEmitter_Conical>(rip, 20);
	pc.transform.p = { 0,0,-100 };

	RenderItem_Prefab ripParticulaAzul(CreateShape(physx::PxSphereGeometry(0.8f)), Vector4(0.3, 0.3, 1, 1));

	pc.SetEmittingFunction(Vector3D(0, 1, 0).normalize(), 15, 0, 3, 100, GenerateBetterParticlePrefab<BetterParticle<>>(ripParticulaAzul, 8), GetParticleSystem("1"));

	GetParticleSystem("1")->addParticle(pc);

	//Cónica-orientada-normal

	Particle_Prefab<ParticleEmitter_Conical_Normal> pcn = GenerateBetterParticlePrefab<ParticleEmitter_Conical_Normal>(rip, 20);
	pcn.transform.p = { 100,0,0 };

	RenderItem_Prefab ripParticulaAzul2(CreateShape(physx::PxSphereGeometry(0.5f)), Vector4(0.5, 0.5, 1, 1));

	pcn.SetEmittingFunction(Vector3D(0, 1, 0).normalize(), 15, 2, 3, 100, GenerateBetterParticlePrefab<BetterParticle<>>(ripParticulaAzul2, 8), GetParticleSystem("1"));

	GetParticleSystem("1")->addParticle(pcn);


}
