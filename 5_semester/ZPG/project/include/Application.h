#ifndef APPLICATION_H
#define APPLICATION_H

#include "Scene.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

class Application {
public:
    Application();
    ~Application();

    void initialization();
    void createScenes();
    void run();

    void switchScene(int index); // Method to switch scenes

private:
    GLFWwindow* window;
    std::vector<std::shared_ptr<Scene>> scenes;
    int currentSceneIndex;

    static void errorCallback(int error, const char* description);
};

#endif // APPLICATION_H