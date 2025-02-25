#pragma once

#include "Scenes/Scene.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"

#include "Graphics/Spotlight.h"

#include "Core/Transformation.h"
#include "Graphics/Camera.h"
#include "Graphics/Light.h"
#include "Graphics/Drawable3DObject.h" 
#include <memory>
#include <vector>

class Scene7 : public Scene {
public:
    Scene7(Camera& camera);
    ~Scene7() override = default;

    virtual void addLight(const Light& light);
    virtual const std::vector<Light>& getLights() const;
    virtual void render(float dt) override;

private:
    Camera& camera;
    std::shared_ptr<Spotlight> spotlight;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    float getRandom(float min, float max);
    std::vector<Light> lights;
    std::vector<std::shared_ptr<DrawableObject>> treeDrawables;

    std::vector<std::shared_ptr<Drawable3DObject>> drawable3DObjects; 
};