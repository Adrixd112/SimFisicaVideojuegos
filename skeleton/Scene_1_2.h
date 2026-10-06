#pragma once
#include "Scene.h"
class Scene_1_2 :public Scene
{
public:
	explicit Scene_1_2(std::string name) : Scene(std::move(name)) {}

	void init() override;
};

