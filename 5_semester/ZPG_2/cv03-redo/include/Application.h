#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "Scene.h"

class Application {
public:
    Application();
    ~Application();

    void initialization();
    void createScenes();
    void switchScene(int index);

    void run();

private:
    GLFWwindow* window;
    std::vector<Scene*> scenes;
    int currentSceneIndex = 0;

    static void errorCallback(int error, const char* description);
    void handleInput();
};