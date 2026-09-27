#pragma once
#include "Scene.h"
class Scene_1_1 :public Scene
{
public:
    explicit Scene_1_1(std::string name) : Scene(std::move(name)) {}

    void init() override;

};

