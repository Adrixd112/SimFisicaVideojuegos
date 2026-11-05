#include "Scene_3.h"

void Scene_3::init()
{
	addParticleSystem("1");

	RenderItem_Prefab rip(CreateShape(physx::PxSphereGeometry(2.0f)), Vector4(1, 0, 0, 1));

	//Cónica-orientada-normal

	Particle_Prefab<ParticleEmitter_Conical_Normal> pcn = GenerateBetterParticlePrefab<ParticleEmitter_Conical_Normal>(rip,-1, std::numeric_limits<double>::infinity());
	pcn.transform.p = { 0,0,0 };

	RenderItem_Prefab ripParticulaAzul2(CreateShape(physx::PxSphereGeometry(0.3)), Vector4(0.2, 0.3, 1, 1));

	Particle_Prefab<BetterParticle<>> partAgua = GenerateBetterParticlePrefab<BetterParticle<>>(ripParticulaAzul2, -1, 120);

	addParticle({ 0,0,8 });
	addParticle({ 8,0,0 });
	addParticle({ 0,0,-8 });
	addParticle({ -8,0,0 });

	partAgua.SetWillDieConditions([](BetterParticle<>* self)->bool {return self->transform.p.y <= -1; });

	pcn.SetEmittingFunction(Vector3D(0, 1, 0).normalize(), 30, 1, 1.2,0.5, 100, 
		partAgua,
		GetParticleSystem("1"));

	GetParticleSystem("1")->addParticle(pcn);
	GetParticleSystem("1")->addForceGenerator(new GravityForceGenerator(-9.81));
	GetParticleSystem("1")->addForceGenerator(new WindForceGenerator({ 0,0,1 }, 8.33f, { 0,100,0 }, {200,190,200}));
}
