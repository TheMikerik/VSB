// Scene3.h
#pragma once

#include "Scenes/Scene.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"
#include "Core/Transformation.h"
#include "Graphics/Camera.h"
#include "Graphics/Light.h"
#include <memory>
#include <vector>

class Scene3 : public Scene {
public:
    Scene3(Camera& camera);
    ~Scene3() override = default;
    virtual void switchShader() override;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
};