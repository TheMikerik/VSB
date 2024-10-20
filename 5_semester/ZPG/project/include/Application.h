#ifndef APPLICATION_H
#define APPLICATION_H

#include "Scene.h"
#include <GL/glew.h>
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
    void switchScene(int index);

private:
    GLFWwindow* window;
    std::vector<std::shared_ptr<Scene>> scenes;
    int currentSceneIndex;

    int selectedDrawableIndex = 0;
    void handleInput();

    static void errorCallback(int error, const char* description);
};

#endif // APPLICATION_H