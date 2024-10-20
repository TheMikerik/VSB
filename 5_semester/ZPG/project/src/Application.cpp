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
    std::srand(static_cast<unsigned int>(std::time(0)));

    auto scene1 = std::make_shared<Scene>();
    auto scene2 = std::make_shared<Scene>();

    auto shader1 = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    auto shader2 = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_red.glsl");
    auto shader3 = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_purple.glsl");
    auto shader4 = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_green.glsl");

    std::vector<std::shared_ptr<ShaderProgram>> shaders = {shader1, shader3, shader4};


    std::vector<float> bushesVertices(std::begin(bushes), std::end(bushes));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    std::vector<float> triangleVertices(std::begin(triangle), std::end(triangle));

    auto bushesModel = std::make_shared<Model>(bushesVertices);
    auto treeModel = std::make_shared<Model>(treeVertices);
    auto triangleModel = std::make_shared<Model>(triangleVertices);

    for (int i = 0; i < 3; ++i)
    {
        auto randomShader = shaders[std::rand() % shaders.size()];
        auto bushesDrawable = std::make_shared<DrawableObject>(bushesModel, randomShader);

        Transformation bushesTrans;
        bushesTrans.translate(glm::vec3(static_cast<float>(std::rand() % 200 - 100) / 100.0f, 
                                        static_cast<float>(std::rand() % 200 - 100) / 100.0f, 
                                        static_cast<float>(std::rand() % 200 - 100) / 100.0f));
        bushesTrans.rotate(static_cast<float>(std::rand() % 360), glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2));
        bushesTrans.scale(glm::vec3(static_cast<float>(std::rand() % 100) / 100.0f));
        bushesDrawable->setTransformation(bushesTrans);

        scene1->addDrawable(bushesDrawable);
    }

    for (int i = 0; i < 5; ++i)
    {
        auto randomShader = shaders[std::rand() % shaders.size()];
        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, randomShader);

        // Apply random transformations
        Transformation treeTrans;
        treeTrans.translate(glm::vec3(static_cast<float>(std::rand() % 200 - 100) / 100.0f, 
                                        static_cast<float>(std::rand() % 200 - 100) / 100.0f, 
                                        static_cast<float>(std::rand() % 200 - 100) / 100.0f));
        treeTrans.rotate(static_cast<float>(std::rand() % 360), glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2));
        treeTrans.scale(glm::vec3(static_cast<float>(std::rand() % 100) / 100.0f));
        treeDrawable->setTransformation(treeTrans);

        scene1->addDrawable(treeDrawable);
    }

    // Scene 2    
    auto triangleDrawable = std::make_shared<DrawableObject>(triangleModel, shader2);
    auto tree2 = std::make_shared<DrawableObject>(treeModel, shader2);

    Transformation t2reeTrans;
    t2reeTrans.translate(glm::vec3(0.0f, -0.9f, 1.0f));
    t2reeTrans.scale(glm::vec3(0.2f));
    tree2->setTransformation(t2reeTrans);

    scene2->addDrawable(triangleDrawable);
    scene2->addDrawable(tree2);

    // Add scenes to application
    scenes.push_back(scene1);
    scenes.push_back(scene2);
}

void Application::run()
{
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.59f, 0.76f, 0.92f, 1.0f);
    createScenes();

    if (!scenes.empty()) {
        selectedDrawableIndex = 0;
        std::cout << "Selected Drawable Index: " << selectedDrawableIndex << std::endl;
    }

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (currentSceneIndex >= 0 && currentSceneIndex < scenes.size()) {
            scenes[currentSceneIndex]->render();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        handleInput();
    }

    glDisable(GL_DEPTH_TEST);
}


void Application::handleInput()
{
    if (currentSceneIndex < 0 || currentSceneIndex >= scenes.size()) {
        return;
    }

    auto& currentScene = scenes[currentSceneIndex];
    auto& drawables = currentScene->getDrawables();

    if (drawables.empty()) {
        return;
    }

    // Clamp the selectedDrawableIndex
    if (selectedDrawableIndex >= drawables.size()) {
        selectedDrawableIndex = 0;
    }

    auto selectedDrawable = drawables[selectedDrawableIndex];

    float translationStep = 0.05f;
    float rotationStep = 5.0f; // degrees
    float scaleStep = 0.05f;

    // Translation Controls
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        // Move on positive X axis
        Transformation trans = selectedDrawable->getTransformation();
        trans.translate(glm::vec3(translationStep, 0.0f, 0.0f));
        selectedDrawable->setTransformation(trans);
        std::cout << "Translated +X" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        // Move on negative X axis
        Transformation trans = selectedDrawable->getTransformation();
        trans.translate(glm::vec3(-translationStep, 0.0f, 0.0f));
        selectedDrawable->setTransformation(trans);
        std::cout << "Translated -X" << std::endl;
    }


    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        // Move on positive Y axis
        Transformation trans = selectedDrawable->getTransformation();
        trans.translate(glm::vec3(0.0f, translationStep, 0.0f));
        selectedDrawable->setTransformation(trans);
        std::cout << "Translated +Y" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        // Move on negative Y axis
        Transformation trans = selectedDrawable->getTransformation();
        trans.translate(glm::vec3(0.0f, -translationStep, 0.0f));
        selectedDrawable->setTransformation(trans);
        std::cout << "Translated -Y" << std::endl;
    }


    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        // Move on positive Z axis
        Transformation trans = selectedDrawable->getTransformation();
        trans.translate(glm::vec3(0.0f, 0.0f, translationStep));
        selectedDrawable->setTransformation(trans);
        std::cout << "Translated +Z" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        // Move on negative Z axis
        Transformation trans = selectedDrawable->getTransformation();
        trans.translate(glm::vec3(0.0f, 0.0f, -translationStep));
        selectedDrawable->setTransformation(trans);
        std::cout << "Translated -Z" << std::endl;
    }

    // Scaling Controls
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        // Make the object bigger
        Transformation trans = selectedDrawable->getTransformation();
        trans.scale(glm::vec3(1.0f + scaleStep));
        selectedDrawable->setTransformation(trans);
        std::cout << "Scaled Up" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        // Make the object smaller
        Transformation trans = selectedDrawable->getTransformation();
        trans.scale(glm::vec3(1.0f - scaleStep));
        selectedDrawable->setTransformation(trans);
        std::cout << "Scaled Down" << std::endl;
    }

    // Rotation Controls
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        // Rotate on positive X axis
        Transformation trans = selectedDrawable->getTransformation();
        trans.rotate(rotationStep, glm::vec3(1.0f, 0.0f, 0.0f));
        selectedDrawable->setTransformation(trans);
        std::cout << "Rotated +X" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        // Rotate on negative X axis
        Transformation trans = selectedDrawable->getTransformation();
        trans.rotate(-rotationStep, glm::vec3(1.0f, 0.0f, 0.0f));
        selectedDrawable->setTransformation(trans);
        std::cout << "Rotated -X" << std::endl;
    }

    // Switching to the next object
    static bool enterPressedLastFrame = false;
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        if (!enterPressedLastFrame) { // Detect key press event
            selectedDrawableIndex = (selectedDrawableIndex + 1) % drawables.size();
            std::cout << "Switched to Drawable Index: " << selectedDrawableIndex << std::endl;
            enterPressedLastFrame = true;
        }
    } else {
        enterPressedLastFrame = false;
    }

    // Switching between scenes
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        switchScene(0);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        switchScene(1);
    }
}

void Application::switchScene(int index)
{
    if (index >=0 && index < scenes.size()) {
        currentSceneIndex = index;
        selectedDrawableIndex = 0;
    } else {
        std::cerr << "Invalid scene index: " << index << std::endl;
    }
}