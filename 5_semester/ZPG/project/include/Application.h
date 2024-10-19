// Application.h
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>

struct Model {
    GLuint VAO;
    GLuint VBO;
    GLsizei vertexCount;
    GLuint shaderProgram;
};

class Application {
public:
    Application();
    ~Application();

    void initialization();
    void createModels();
    void run();

private:
    GLFWwindow* window;
    std::vector<Model> models;

    static void errorCallback(int error, const char* description);
    
    std::string loadShaderSource(const std::string& filePath);
    GLuint createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    void compileShader(const std::string& source, GLuint shader);
    void linkProgram(GLuint program, GLuint vertexShader, GLuint fragmentShader);

    std::vector<float> loadObject(const std::string& filePath);
    void addModel(const std::vector<float>& vertices, const std::string& fragmentPath);
};