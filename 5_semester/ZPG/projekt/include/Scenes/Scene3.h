// Scene3.h
#pragma once

#include "Scene.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"
#include "Camera.h"
#include "Light.h"
#include <memory>
#include <vector>

class Scene3 : public Scene {
public:
    Scene3(Camera& camera, Light& pointLight);
    ~Scene3() override = default;
    virtual void switchShader() override;

private:
    Camera& camera;
    Light& pointLight;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
};