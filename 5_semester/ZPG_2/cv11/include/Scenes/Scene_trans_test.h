// Scene_trans_test.h
#pragma once

#include "Scenes/Scene.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"
#include "Core/Transformation.h"
#include "Graphics/Camera.h"
#include "Graphics/Light.h"
#include <memory>
#include <vector>

class Scene_trans_test : public Scene {
public:
    Scene_trans_test(Camera& camera);
    ~Scene_trans_test() override = default;
    virtual void switchShader() override;

    virtual void addLight(const Light& light);
    virtual const std::vector<Light>& getLights() const;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    std::vector<Light> lights;
    std::vector<std::shared_ptr<DrawableObject>> fixedShaderDrawables;
};