#pragma once

#include "Scenes/Scene.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"
#include "Core/Transformation.h"
#include "Graphics/Camera.h"
#include "Graphics/Light.h"
#include <memory>
#include <vector>

struct LightDrawableWithDirection {
    std::shared_ptr<DrawableObject> drawable;
    glm::vec3 direction;
    LightDrawableWithDirection(std::shared_ptr<DrawableObject> drawable, glm::vec3 direction) 
        : drawable(drawable), direction(direction) {}
};

class Scene5 : public Scene {
public:
    Scene5(Camera& camera);
    ~Scene5() override = default;

    virtual void addLight(const Light& light);
    virtual const std::vector<Light>& getLights() const;
    virtual void render(float dt) override;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    float getRandom(float min, float max);
    std::vector<Light> lights;
    std::vector<std::shared_ptr<DrawableObject>> treeDrawables;
    std::vector<LightDrawableWithDirection> lightDrawablesWithDirection;
};