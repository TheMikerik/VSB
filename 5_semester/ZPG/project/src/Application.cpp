#include "Application.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "DrawableObject.h"
#include "Transformation.h"

#include "../models/bushes.h"
#include "../models/tree.h"
#include "../models/triangle.h"

#include <iostream>
#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Application::errorCallback(int error, const char* description)
{
    // Forward to the instance's error callback if needed
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

Application::Application()
    : window(nullptr), currentSceneIndex(0) {}

Application::~Application()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initialization()
{
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit()) {
        std::cerr << "ERROR: could not start GLFW3" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "OpenGL Application", nullptr, nullptr);
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

void Application::createScenes()
{
    // Scene 1
    auto scene1 = std::make_shared<Scene>();

    // Load shader program (shared across objects)
    auto shader1 = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");

    // Create Model instances
    std::vector<float> bushesVertices(std::begin(bushes), std::end(bushes));
    auto bushesModel = std::make_shared<Model>(bushesVertices);

    std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    auto treeModel = std::make_shared<Model>(treeVertices);

    // Create DrawableObjects
    auto bushesDrawable = std::make_shared<DrawableObject>(bushesModel, shader1);
    auto treeDrawable = std::make_shared<DrawableObject>(treeModel, shader1);

    // Apply transformations
    // Transformation bushesTrans;
    // bushesTrans.translate(glm::vec3(-0.0f, -0.0f, -0.0f));
    // bushesTrans.rotate(45.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    // bushesTrans.scale(glm::vec3(0.5f));
    // bushesDrawable->setTransformation(bushesTrans);

    // Transformation treeTrans;
    // treeTrans.translate(glm::vec3(0.0f, 0.0f, 0.0f));
    // treeTrans.rotate(-30.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    // treeTrans.scale(glm::vec3(1.0f));
    // treeDrawable->setTransformation(treeTrans);

    // Add to scene
    scene1->addDrawable(bushesDrawable);
    scene1->addDrawable(treeDrawable);

    // Scene 2 (example: different objects or different shaders)
    auto scene2 = std::make_shared<Scene>();

    // Maybe use a different shader
    auto shader2 = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_red.glsl");

    // Create Model for triangle
    std::vector<float> triangleVertices(std::begin(triangle), std::end(triangle));
    auto triangleModel = std::make_shared<Model>(triangleVertices);
    auto triangleDrawable = std::make_shared<DrawableObject>(triangleModel, shader2);

    // Apply transformations
    // Transformation triangleTrans;
    // triangleTrans.translate(glm::vec3(0.0f, 0.0f, 0.0f));
    // triangleTrans.rotate(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    // triangleTrans.scale(glm::vec3(1.0f));
    // triangleDrawable->setTransformation(triangleTrans);

    scene2->addDrawable(triangleDrawable);

    // Add scenes to application
    scenes.push_back(scene1);
    scenes.push_back(scene2);
}

void Application::run()
{
    glEnable(GL_DEPTH_TEST);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (currentSceneIndex >= 0 && currentSceneIndex < scenes.size()) {
            scenes[currentSceneIndex]->render();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Input handling for switching scenes
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            switchScene(0);
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            switchScene(1);
        }
    }

    glDisable(GL_DEPTH_TEST);
}

void Application::switchScene(int index)
{
    if (index >=0 && index < scenes.size()) {
        currentSceneIndex = index;
        std::cout << "Switched to scene " << index << std::endl;
    } else {
        std::cerr << "Invalid scene index: " << index << std::endl;
    }
}