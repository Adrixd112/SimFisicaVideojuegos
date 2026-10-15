#pragma once
#include "Scene.h"
class Scene_1_2b :public Scene
{
public:
	explicit Scene_1_2b(std::string name) : Scene(std::move(name)) { sCamera = new Camera({ 0,0,0 }, { 1,0,0 }); }

	~Scene_1_2b() override { delete sCamera; }
	void init() override;

	void keyPress(unsigned char key, const physx::PxTransform& cameraTransform);
};

