#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Application {
public:
    Application();
    ~Application();

    bool initialization();
    void createShaders();
    void createModels();
    void run();
    
private:
    GLFWwindow* window;
    Shader* shaderProgram;
    Model* model;

    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 ModelMatrix;

    static void error_callback(int error, const char* description);
};

#endif // APPLICATION_H