#pragma once

#include "Scene.h"
#include <memory>

class Scene2 : public Scene {
public:
    Scene2();
    ~Scene2() = default;

private:
    void createSpheres();
};