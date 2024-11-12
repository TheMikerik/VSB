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

    virtual void addLight(const Light& light);
    virtual const std::vector<Light>& getLights() const;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    std::vector<Light> lights;
};