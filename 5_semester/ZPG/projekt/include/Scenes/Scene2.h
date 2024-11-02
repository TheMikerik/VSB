// Scene2.h
#pragma once

#include "Scene.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"
#include "Camera.h"
#include <memory>
#include <vector>

class Scene2 : public Scene {
public:
    Scene2(Camera& camera);
    ~Scene2() override = default;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
};