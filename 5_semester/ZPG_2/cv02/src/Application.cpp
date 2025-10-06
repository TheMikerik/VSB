// Application.cpp
#include "Application.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <vector>

Application::Application() : window(nullptr) {}

Application::~Application() {
    for (auto model : models) {
        delete model;
    }
    models.clear();

    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Application::errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void Application::initialization() {
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit()) {
        std::cerr << "ERROR: could not start GLFW3" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(800, 600, "OpenGL App", nullptr, nullptr);
    if (!window) {
        std::cerr << "ERROR: could not create GLFW window" << std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }
    
    glfwSetKeyCallback(window, keyCallback);

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error initializing GLEW: " << glewGetErrorString(err) << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Print OpenGL and GLFW information
    std::cout << "\nOpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    std::cout << "Using GLFW " << major << "." << minor << "." << revision << std::endl;

    // Set the viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

std::vector<float> Application::loadObject(const std::string& filePath) {
    std::vector<float> points;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open object file: " << filePath << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            // Remove the 'f' suffix if present
            if (token.back() == 'f') {
                token.pop_back();
            }
            float value = std::stof(token);
            points.push_back(value);
        }
    }

    return points;
}

void Application::addModel(const std::vector<float>& vertices, const std::string& fragmentPath) {
    // Dynamically allocate a new Model instance
    Model* model = new Model(vertices, fragmentPath, "./shaders/vertex_shader.glsl");

    // Add the model to the list
    models.push_back(model);
}

void Application::createModels() {
    std::vector<float> square = loadObject("./models/square.obj");
    addModel(square, "./shaders/fragment_shader.glsl");

    std::vector<float> triangle = loadObject("./models/triangle.obj");
    addModel(triangle, "./shaders/fragment_shader_redish.glsl");

    std::vector<float> test = loadObject("./models/test.obj");
    addModel(test, "./shaders/fragment_shader.glsl");
}

void Application::run() {
    glEnable(GL_DEPTH_TEST);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render each model
        for (const auto& model : models) {
            model->render();
        }

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDisable(GL_DEPTH_TEST);
}