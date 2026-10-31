#include "Scene_2.h"

void Scene_2::init()
{
	addParticleSystem("1");


	ParticleEmitter_Rectangular_Ortogonal p = GenerateBetterParticlePrefab<ParticleEmitter_Rectangular_Ortogonal>({0,0,0});

	p.SetEmittingFunction({ 1,1,0 }, 20, 20, 2, GenerateBetterParticlePrefab<ParticleEmitter_Rectangular_Ortogonal>({ 0,0,0 }), GetParticleSystem("1"));

	GetParticleSystem("1")->addParticle(p);
}
