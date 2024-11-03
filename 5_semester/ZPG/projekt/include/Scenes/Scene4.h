// Scene4.h
#pragma once

#include "Scenes/Scene.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"
#include "Core/Transformation.h"
#include "Graphics/Camera.h"
#include "Graphics/Light.h"
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