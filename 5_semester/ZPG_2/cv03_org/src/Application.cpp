// Application.cpp
#include "Application.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "Scene1.h"
#include "Scene2.h"

Application::Application() : window(nullptr) {}

Application::~Application() {
    for (auto* scene : scenes) {
        delete scene;
    }
    scenes.clear();
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

void Application::handleInput() {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        switchScene(0);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        switchScene(1);
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

    std::cout << "\n==========INIT INFO==========" << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    std::cout << "Using GLFW " << major << "." << minor << "." << revision << std::endl;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    std::cout << "Framebuffer size: " << width << "x" << height << std::endl;
    std::cout << "===============================\n" << std::endl;
}

void Application::createScenes() {
    Scene1* scene1 = new Scene1();
    Scene2* scene2 = new Scene2();

    scenes.push_back(scene1);
    scenes.push_back(scene2);
}

void Application::run() {
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.59f, 0.76f, 0.92f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the current scene
        if (currentSceneIndex >= 0 && currentSceneIndex < scenes.size()) {
            scenes[currentSceneIndex]->render();
        }

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();

        handleInput();
    }

    glDisable(GL_DEPTH_TEST);
}

void Application::switchScene(int index) {
    if (index >= 0 && index < scenes.size()) {
        currentSceneIndex = index;
        std::cout << "Switched to scene " << index << std::endl;
    } else {
        std::cerr << "Invalid scene index: " << index << std::endl;
    }
}