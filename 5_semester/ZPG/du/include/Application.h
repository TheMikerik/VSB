#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Model.h"
#include "Cube.h"
#include "Square.h"
#include "Triangle.h"
#include <vector>

class Application {
public:
    GLFWwindow* window;
    Shader* shaderProgram;
    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 ModelMatrix;

    // Vektor modelů
    std::vector<Model*> models;
    std::vector<glm::mat4> modelMatrices;

    Application();
    ~Application();

    bool initialization();
    void createShaders();
    void createModels();
    void run();

    // Deklarace error_callback jako statické funkce
    static void error_callback(int error, const char* description);
};

#endif // APPLICATION_H