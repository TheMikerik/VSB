#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "Scenes/Scene.h"
#include "Graphics/Camera.h"
#include "Core/Controller.h"
#include "Graphics/Light.h" 

#include "Scenes/Scene2.h"
#include "Scenes/Scene1.h"

class Application {
public:
    Application();
    ~Application();

    void initialization();
    void createScenes();
    void run();

private:
    GLFWwindow* window;
    std::vector<std::shared_ptr<Scene>> scenes;
    int currentSceneIndex;

    Camera camera;

    std::unique_ptr<Controller> controller;

    Light pointLight;
    std::vector<Light> fireflies;
};

extern Application App;