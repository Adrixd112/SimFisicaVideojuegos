#include "Scene_2.h"

void Scene_2::init()
{
	addParticleSystem("1");

	RenderItem_Prefab rip = GenerateRenderItemPrefab(CreateShape(physx::PxSphereGeometry(1.0f)), Vector4(1, 0, 0, 1));

	ParticleEmitter_Rectangular_Ortogonal p = GenerateBetterParticlePrefab<ParticleEmitter_Rectangular_Ortogonal>(rip,{0,0,0});


	p.SetEmittingFunction({ 1,1,0 }, 20, 20, 2, GenerateBetterParticlePrefab<BetterParticlePadre>({ 0,0,0 }, {0,0,1}), GetParticleSystem("1"));

	GetParticleSystem("1")->addParticle(p);

	int i = 0;
}
