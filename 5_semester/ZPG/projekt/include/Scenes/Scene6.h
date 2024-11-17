// Scene6.h
#pragma once

#include "Scenes/Scene.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"
#include "Core/Transformation.h"
#include "Graphics/Camera.h"
#include "Graphics/Light.h"
#include <memory>
#include <vector>

class Scene6 : public Scene {
public:
    Scene6(Camera& camera);
    ~Scene6() override = default;

    virtual void render(float dt) override;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    float getRandom(float min, float max);
    std::vector<std::shared_ptr<DrawableObject>> treeDrawables;

    glm::vec3 spotlightPos;
    glm::vec3 spotlightDir;
};