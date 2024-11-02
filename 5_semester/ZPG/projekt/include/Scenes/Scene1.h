// Scene1.h
#pragma once

#include "Scene.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"
#include "Camera.h"
#include <memory>
#include <vector>

class Scene1 : public Scene {
public:
    Scene1(Camera& camera);
    ~Scene1() override = default;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;

    float getRandom(float min, float max);
};