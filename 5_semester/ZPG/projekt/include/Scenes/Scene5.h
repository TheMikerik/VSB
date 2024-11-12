// Scene5.h
#pragma once

#include "Scenes/Scene.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"
#include "Core/Transformation.h"
#include "Graphics/Camera.h"
#include "Graphics/Light.h"
#include <memory>
#include <vector>

class Scene5 : public Scene {
public:
    Scene5(Camera& camera);
    ~Scene5() override = default;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;

    float getRandom(float min, float max);
};