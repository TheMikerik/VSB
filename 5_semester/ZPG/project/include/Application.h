#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Scene.h"
#include "Camera.h"

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
    float lastX;
    float lastY;
    bool firstMouse;

    float deltaTime;
    float lastFrame;

    size_t selectedDrawableIndex;
    bool rotationEnabled;

    void handleInput();
    void switchScene(int index);
    float getRandom(float min, float max);

    static void errorCallback(int error, const char* description);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    // Pro pristup k instanci ze static callbacku
    static Application* instance;
};