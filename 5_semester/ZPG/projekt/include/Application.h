#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Scene.h"
#include "Camera.h"
#include "Controller.h"

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
};