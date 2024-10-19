#include "Application.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

Application::Application() : window(nullptr), VAO(0), VBO(0), shaderProgram(0) {}

Application::~Application() {
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "OpenGL App", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    glewInit();

    printf("\nOpenGL Version: %s\n",glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

std::string Application::loadShaderSource(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    std::stringstream shaderStream;
    // kopirovani obsahu souboru do stringstream
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

void Application::createShaders() {
    std::string vertexShaderSource = loadShaderSource("./shaders/vertex_shader.glsl");

    std::string fragmentShaderSource = loadShaderSource("./shaders/fragment_shader.glsl");

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexShaderSource, vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentShaderSource, fragmentShader);

    shaderProgram = glCreateProgram();
    linkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Application::compileShader(const std::string& source, GLuint shader) {
    const char* shaderCode = source.c_str();
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        fprintf(stderr, "ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
        exit(EXIT_FAILURE);
    }
}

void Application::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
        exit(EXIT_FAILURE);
    }
}

std::vector<float> Application::loadObject(const std::string& filePath) {
    std::vector<float> points;
    std::ifstream file(filePath);
    float value;
    while (file >> value) {
        points.push_back(value);
    }
    return points;
}

void Application::createModels() {
    std::vector<float> points = loadObject("./objects/square.obj");

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Application::run() {
  // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
    GLint infoLogLength;
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
    GLchar *strInfoLog = new GLchar[infoLogLength + 1];
    glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
    fprintf(stderr, "Linker failure: %s\n", strInfoLog);
    delete[] strInfoLog;
	}
}
