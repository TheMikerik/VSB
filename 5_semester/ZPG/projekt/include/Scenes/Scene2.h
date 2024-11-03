// Scene2.h
#pragma once

#include "Scenes/Scene.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"
#include "Core/Transformation.h"
#include "Graphics/Camera.h"
#include <memory>
#include <vector>

class Scene2 : public Scene {
public:
    Scene2(Camera& camera);
    ~Scene2() override = default;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;

    float getRandom(float min, float max);
};