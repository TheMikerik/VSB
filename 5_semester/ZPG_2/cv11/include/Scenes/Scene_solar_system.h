#pragma once

#include "Scenes/Scene.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"
#include "Core/Transformation.h"
#include "Core/Transformation/DynamicRotationOperation.h"
#include "Graphics/Camera.h"
#include "Graphics/Light.h"
#include <memory>
#include <vector>

struct Planet {
    std::shared_ptr<DrawableObject> drawable;
    float distanceFromSun;
    float speed;
    float position;
    float scale;
    glm::vec3 worldPosition;

    float selfRotationSpeed;
    float selfRotationAngle;
    
    Planet(std::shared_ptr<DrawableObject> d, float dfs, float s, float sc, float srs = 1.0f, float sra = 48.0f)
    : drawable(d), distanceFromSun(dfs), speed(s), position(0.0f), scale(sc),
      worldPosition(glm::vec3(0.0f)), selfRotationSpeed(srs), selfRotationAngle(sra) {}
};

class Scene_solar_system : public Scene {
public:
    Scene_solar_system(Camera& camera);
    ~Scene_solar_system() override = default;

    void addLight(const Light& light);
    const std::vector<Light>& getLights() const;
    void render(float dt) override;

private:
    Camera& camera;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    std::vector<Light> lights;
    std::vector<Planet> planets;

    std::shared_ptr<DynamicRotationOperation> moonDynamicRotation;
    size_t earthIndex;
    size_t moonIndex;
};