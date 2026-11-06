#pragma once
#include "ForceGenerator.h"
class WindForceGenerator : public ForceGenerator
{	
	const float k1 = 4;
	const float k2 = 0;

	Vector3D windvel;
	//el origen está en el centro del area.
	Vector3D origin;
	//el origen está en el centro del area.
	Vector3D areaSize;
public:
	WindForceGenerator() : windvel(Vector3D::Zero), origin(Vector3D::Zero), areaSize(Vector3D::Infinity) {};
	WindForceGenerator(Vector3D windvel,Vector3D areaOrigin,Vector3D areaSize) : windvel(windvel),origin(areaOrigin),areaSize(areaSize) {};
	WindForceGenerator(Vector3D windDirection,float windSpeed, Vector3D areaOrigin, Vector3D areaSize) : windvel(windDirection.normalize()*windSpeed), origin(areaOrigin), areaSize(areaSize) {};
	virtual Vector3D CalculateForce(Particle* p);
};

