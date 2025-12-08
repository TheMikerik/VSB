#ifndef SCENE6_H
#define SCENE6_H

#include "Scene.h"
#include "Graphics/Camera.h"
#include "Graphics/Spotlight.h"
#include <memory>
#include <vector>

class Scene6 : public Scene {
public:
    Scene6(Camera& cam);
    void render(float dt) override;
    void toggleFlashlight();

private:
    Camera& camera;
    std::shared_ptr<Spotlight> spotlight;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    std::vector<std::shared_ptr<DrawableObject>> treeDrawables;
    bool flashlightEnabled; 

    float getRandom(float min, float max);
};

#endif