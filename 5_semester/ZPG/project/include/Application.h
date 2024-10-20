// Application.h (partial)
#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Scene.h"
#include "Camera.h"

// Add Mouse Callback
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

    // Camera
    Camera camera;
    float lastX;
    float lastY;
    bool firstMouse;

    // Timing
    float deltaTime;
    float lastFrame;

    // Selected Drawable
    size_t selectedDrawableIndex;

    // Input handling
    void handleInput();
    void switchScene(int index);
    float getRandom(float min, float max);

    // Static callbacks
    static void errorCallback(int error, const char* description);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    // To access member variables in static callbacks
    static Application* instance;
};

#endif // APPLICATION_H