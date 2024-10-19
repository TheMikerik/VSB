// Application.cpp
#include "Application.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

Application::Application() : window(nullptr) {}

Application::~Application() {
    // Delete shader programs for each model
    for (const auto& model : models) {
        glDeleteVertexArrays(1, &model.VAO);
        glDeleteBuffers(1, &model.VBO);
        glDeleteProgram(model.shaderProgram);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::errorCallback(int error, const char* description) {
    fputs(description, stderr);
}

void Application::initialization() {
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    // Set OpenGL version to 3.3 and core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(800, 600, "OpenGL App", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Print OpenGL and GLFW information
    printf("\nOpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    // Set the viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

std::string Application::loadShaderSource(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        fprintf(stderr, "Failed to open shader file: %s\n", filePath.c_str());
        exit(EXIT_FAILURE);
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

GLuint Application::createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
    // Load shader sources
    std::string vertexSource = loadShaderSource(vertexPath);
    std::string fragmentSource = loadShaderSource(fragmentPath);

    // Create and compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexSource, vertexShader);

    // Create and compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentSource, fragmentShader);

    // Create shader program and link shaders
    GLuint program = glCreateProgram();
    linkProgram(program, vertexShader, fragmentShader);

    // Shaders can be deleted after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Application::compileShader(const std::string& source, GLuint shader) {
    const char* shaderCode = source.c_str();
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::string shaderType = (shader == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
        fprintf(stderr, "ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", shaderType.c_str(), infoLog);
        exit(EXIT_FAILURE);
    }
}

void Application::linkProgram(GLuint program, GLuint vertexShader, GLuint fragmentShader) {
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for linking errors
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
        exit(EXIT_FAILURE);
    }
}

std::vector<float> Application::loadObject(const std::string& filePath) {
    std::vector<float> points;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        fprintf(stderr, "Failed to open object file: %s\n", filePath.c_str());
        exit(EXIT_FAILURE);
    }

    float value;
    while (file >> value) {
        points.push_back(value);
    }

    return points;
}

void Application::addModel(const std::vector<float>& vertices, const std::string& fragmentPath) {
    Model model;

    // Generate and bind VAO
    glGenVertexArrays(1, &model.VAO);
    glBindVertexArray(model.VAO);

    // Generate and bind VBO
    glGenBuffers(1, &model.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, model.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Define vertex attribute (assuming position only)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    model.vertexCount = static_cast<GLsizei>(vertices.size() / 3); // Assuming 3 floats per vertex

    // Create shader program for this model
    // Assuming all models share the same vertex shader
    model.shaderProgram = createShaderProgram("./shaders/vertex_shader.glsl", fragmentPath);

    // Add the model to the list
    models.push_back(model);
}

void Application::createModels() {
    // Load object data and add models with different fragment shaders

    // Model 1: Square with red color
    std::vector<float> square = loadObject("./models/square.obj");
    addModel(square, "./shaders/fragment_shader_red.glsl");

    // Model 2: Triangle with green color
    std::vector<float> triangle = loadObject("./models/triangle.obj");
    addModel(triangle, "./shaders/fragment_shader_green.glsl");

    // Model 3: Test object with blue color
    std::vector<float> test = loadObject("./models/test.obj");
    addModel(test, "./shaders/fragment_shader_purple.glsl");
}

void Application::run() {
    glEnable(GL_DEPTH_TEST);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render each model with its own shader
        for (const auto& model : models) {
            glUseProgram(model.shaderProgram);
            glBindVertexArray(model.VAO);
            glDrawArrays(GL_TRIANGLES, 0, model.vertexCount);
            glBindVertexArray(0);
        }

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDisable(GL_DEPTH_TEST);
}