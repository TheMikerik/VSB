// Scene3.h
#pragma once

#include "Scene.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"
#include "Camera.h"
#include <memory>
#include <vector>

class Scene3 : public Scene {
public:
    Scene3(Camera& camera);
    ~Scene3() override = default;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
};