#pragma once

#include "Scene.h"
#include <memory>

class Scene1 : public Scene {
public:
    Scene1();
    ~Scene1() = default;

private:
    void createTriangle();
};
