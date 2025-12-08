#pragma once

#include "Scenes/Scene.h"
#include "Graphics/Camera.h"
#include "Core/Transformation/BezierCurveOperation.h"
#include "Core/Transformation/ScaleOperation.h"
#include "Shaders/ShaderProgram.h"
#include "Graphics/Spotlight.h"
#include <memory>
#include <vector>
#include <glm/glm.hpp>

class Scene_bezier : public Scene {
public:
    Scene_bezier(Camera& camera);
    void render(float dt) override;
    
    void addControlPoint(const glm::vec3& point);
    void toggleFlashlight();

private:
    Camera& camera;
    std::shared_ptr<BezierCurveOperation> bezierOp;
    std::vector<glm::vec3> controlPoints;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    std::shared_ptr<Spotlight> spotlight;
    std::vector<std::shared_ptr<DrawableObject>> treeDrawables;
    std::shared_ptr<DrawableObject> shrekDrawable;
    bool flashlightEnabled;
    
    float getRandom(float min, float max);
};