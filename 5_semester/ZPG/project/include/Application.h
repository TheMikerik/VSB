#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <string>

struct Model {
    GLuint VAO;
    GLuint VBO;
    GLsizei vertexCount;
};

class Application {
public:
    Application();
    ~Application();

    void initialization();
    void createShaders();
    void createModels();
    void run();

private:
    GLFWwindow* window;
    GLuint shaderProgram;
    std::vector<Model> models;

    static void errorCallback(int error, const char* description);
    void compileShader(const std::string& source, GLuint shader);
    void linkProgram(GLuint vertexShader, GLuint fragmentShader);
    std::vector<float> loadObject(const std::string& filePath);
    std::string loadShaderSource(const std::string& filePath);
    void addModel(const std::vector<float>& vertices);
};