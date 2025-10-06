// Application.h
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "Model.h"

class Application {
public:
    Application();
    ~Application();

    void initialization();
    void createModels();
    void run();

private:
    GLFWwindow* window;
    std::vector<Model*> models;

    static void errorCallback(int error, const char* description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    std::vector<float> loadObject(const std::string& filePath);
    void addModel(const std::vector<float>& vertices, const std::string& fragmentPath);
};