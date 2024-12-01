<<<<<<< HEAD
#pragma once
=======
#ifndef SCENE6_H
#define SCENE6_H
>>>>>>> 783003c0f8698c5a6a0d2f713c85ebf89823a7c5

#include "Scene.h"
#include "Graphics/Camera.h"
#include "Graphics/Spotlight.h"
#include <memory>
#include <vector>

class Scene6 : public Scene {
public:
    Scene6(Camera& cam);
    void render(float dt) override;

private:
    Camera& camera;
<<<<<<< HEAD
    std::shared_ptr<Spotlight> spotlight;
=======
    std::shared_ptr<Spotlight> spotlight;    
>>>>>>> 783003c0f8698c5a6a0d2f713c85ebf89823a7c5
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    std::vector<std::shared_ptr<DrawableObject>> treeDrawables;

    float getRandom(float min, float max);
<<<<<<< HEAD
};
=======
};

#endif 
>>>>>>> 783003c0f8698c5a6a0d2f713c85ebf89823a7c5
