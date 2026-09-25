#pragma once
#include "Scene.h"
class Scene_0C :public Scene
{
public:
    explicit Scene_0C(std::string name) : Scene(std::move(name)) {}

    void init() override;
};

