// Controller.h
#pragma once

#include <memory>
#include "Camera.h"
#include "Scene.h"
#include <GLFW/glfw3.h>

class Controller {
public:
    Controller(GLFWwindow* window, Camera& camera, std::vector<std::shared_ptr<Scene>>& scenes);
    ~Controller() = default;

    void handleInput(float deltaTime);
    void setSelectedDrawable(size_t index);
    void setRotationEnabled(bool enabled);
    bool isRotationEnabled() const;

    // Callbacks
    static void errorCallback(int error, const char* description);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
    GLFWwindow* window;
    Camera& camera;
    std::vector<std::shared_ptr<Scene>>& scenes;
    auto& drawables;

    size_t selectedDrawableIndex;
    bool rotationEnabled;

    // Mouse handling
    float lastX;
    float lastY;
    bool firstMouse;

    // Timing
    float deltaTime;
    float lastFrame;

    // Helper functions
    void processKeyboardInput(float deltaTime);
    void processTransformationInput();
};