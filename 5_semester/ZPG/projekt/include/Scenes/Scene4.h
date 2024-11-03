// Scene4.h
#pragma once

#include "Scene.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"
#include "Camera.h"
#include "Light.h"
#include <memory>
#include <vector>

class Scene4 : public Scene {
public:
    Scene4(Camera& camera, Light& pointLight);
    ~Scene4() override = default;

private:
    Camera& camera;
    Light& pointLight;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;

    float getRandom(float min, float max);
};