// Scene1.h
#pragma once

#include "Scenes/Scene.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"
#include "Core/Transformation.h"
#include "Graphics/Camera.h"
#include <memory>
#include <vector>

class Scene1 : public Scene {
public:
    Scene1(Camera& camera);
    ~Scene1() override = default;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
};