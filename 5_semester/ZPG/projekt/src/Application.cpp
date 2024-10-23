// Application.cpp
#include "Application.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "DrawableObject.h"
#include "Transformation.h"
#include "ICameraObserver.h"

#include "../models/bushes.h"
#include "../models/tree.h"
#include "../models/triangle.h"
#include "../models/platform.h"
#include "../models/sphere.h"

#include <iostream>
#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <thread>



Application* Application::instance = nullptr;

void Application::errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

float Application::getRandom(float min, float max)
{
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void Application::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Application::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (instance->firstMouse)
    {
        instance->lastX = static_cast<float>(xpos);
        instance->lastY = static_cast<float>(ypos);
        instance->firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - instance->lastX;
    float yoffset = instance->lastY - static_cast<float>(ypos);

    instance->lastX = static_cast<float>(xpos);
    instance->lastY = static_cast<float>(ypos);

    instance->camera.ProcessMouseMovement(xoffset, yoffset);
}

void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    instance->camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

Application::Application()
    : window(nullptr), currentSceneIndex(0),
        camera(glm::vec3(0.0f, 10.0f, 20.0f)),
        lastX(400.0f), lastY(300.0f), firstMouse(true),
        deltaTime(0.0f), lastFrame(0.0f),
        selectedDrawableIndex(0),
        rotationEnabled(false)
{
    // Set the static instance pointer
    instance = this;
}

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

    window = glfwCreateWindow(1450, 900, "OpenGL Application with Camera", nullptr, nullptr);
    if (!window) {
        std::cerr << "ERROR: could not create GLFW window" << std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    // timto se povoluje vsync
    glfwSwapInterval(1);

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

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::createScenes()
{
    std::srand(static_cast<unsigned int>(std::time(0)));

    auto scene1 = std::make_shared<Scene>();
    auto scene2 = std::make_shared<Scene>();
    auto scene3 = std::make_shared<Scene>();

    auto shader_uni = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    auto shader_red = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_red.glsl");
    auto shader_purple = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_purple.glsl");
    auto shader_green = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_green.glsl");
    auto shader_lambert = std::make_shared<ShaderProgram>("./shaders/lambert_vertex.glsl", "./shaders/lambert_fragment.glsl");


    // std::vector<std::shared_ptr<ShaderProgram>> shaders = {shader_uni, shader_red, shader_purple, shader_green};
    std::vector<std::shared_ptr<ShaderProgram>> shaders = {shader_lambert};

    for(auto& shader : shaders)
    {
        camera.registerObserver(shader.get());
    }

    camera.notifyObservers();

    std::vector<float> bushesVertices(std::begin(bushes), std::end(bushes));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    std::vector<float> triangleVertices(std::begin(triangle), std::end(triangle));
    std::vector<float> platformVertices(std::begin(platform), std::end(platform));
    std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));

    auto bushesModel = std::make_shared<Model>(bushesVertices);
    auto treeModel = std::make_shared<Model>(treeVertices);
    auto triangleModel = std::make_shared<Model>(triangleVertices);
    auto platformModel = std::make_shared<Model>(platformVertices);
    auto sphereModel = std::make_shared<Model>(sphereVertices);

    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_uni);
    scene1->addDrawable(platformDrawable);

    for (int i = 0; i < 300; ++i)
    {
        auto randomShader = shaders[i % 4];
        auto bushesDrawable = std::make_shared<DrawableObject>(bushesModel, randomShader);

        Transformation bushesTrans;
        bushesTrans.translate(glm::vec3(
            getRandom(-15.0f, 15.0f),
            0.0f,
            getRandom(-15.0f, 15.0f)
        ));
        bushesTrans.rotate(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        bushesTrans.scale(glm::vec3(getRandom(1.0f, 3.0f)));
        bushesDrawable->setTransformation(bushesTrans);

        scene1->addDrawable(bushesDrawable);
        
    }

    for (int i = 0; i < 100; ++i)
    {
        auto randomShader = shaders[i % 4];
        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, randomShader);

        Transformation treeTrans;
        treeTrans.translate(glm::vec3(
            getRandom(-15.0f, 15.0f),
            0.0f,
            getRandom(-15.0f, 15.0f)
        ));
        treeTrans.rotate(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        treeTrans.scale(glm::vec3(getRandom(0.2f, 0.8f)));
        treeDrawable->setTransformation(treeTrans);

        scene1->addDrawable(treeDrawable);
    }



    auto triangleDrawable = std::make_shared<DrawableObject>(triangleModel, shader_red);
    auto tree2 = std::make_shared<DrawableObject>(treeModel, shader_red);

    Transformation tree2Trans;
    tree2Trans.translate(glm::vec3(0.0f, -0.9f, 1.0f));
    tree2Trans.scale(glm::vec3(0.2f));
    tree2->setTransformation(tree2Trans);

    scene2->addDrawable(triangleDrawable);
    scene2->addDrawable(tree2);


    std::vector<glm::vec3> positions = {
        glm::vec3(2.0f, 0.0f, 2.0f),
        glm::vec3(-2.0f, 0.0f, 2.0f),
        glm::vec3(2.0f, 0.0f, -2.0f),
        glm::vec3(-2.0f, 0.0f, -2.0f)
    };

    for (auto position : positions){
        auto sphereDrawable = std::make_shared<DrawableObject>(sphereModel, shader_uni);

        Transformation sphereTrans;
        sphereTrans.translate(position);
        sphereDrawable->setTransformation(sphereTrans);
        scene3->addDrawable(sphereDrawable);
    }



    scenes.push_back(scene1);
    scenes.push_back(scene2);
    scenes.push_back(scene3);
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
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clearne screen a jeho buff
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

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime * 2);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime * 2);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime * 2);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime * 2);

    if (selectedDrawableIndex >= drawables.size())
        selectedDrawableIndex = 0;

    auto selectedDrawable = drawables[selectedDrawableIndex];

    float translationStep = 0.05f;
    float rotationStep = 5.0f;
    float scaleStep = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        if (!rotationEnabled){
            Transformation trans = selectedDrawable->getTransformation();
            trans.translate(glm::vec3(translationStep, 0.0f, 0.0f));
            selectedDrawable->setTransformation(trans);
            std::cout << "Translated +X" << std::endl;
        } else {
            Transformation trans = selectedDrawable->getTransformation();
            trans.rotate(rotationStep, glm::vec3(1.0f, 0.0f, 0.0f));
            selectedDrawable->setTransformation(trans);
            std::cout << "Rotated +X" << std::endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        if (!rotationEnabled){
            Transformation trans = selectedDrawable->getTransformation();
            trans.translate(glm::vec3(-translationStep, 0.0f, 0.0f));
            selectedDrawable->setTransformation(trans);
            std::cout << "Translated -X" << std::endl;
        } else {
            Transformation trans = selectedDrawable->getTransformation();
            trans.rotate(-rotationStep, glm::vec3(1.0f, 0.0f, 0.0f));
            selectedDrawable->setTransformation(trans);
            std::cout << "Rotated -X" << std::endl;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        if (!rotationEnabled){
            Transformation trans = selectedDrawable->getTransformation();
            trans.translate(glm::vec3(0.0f, translationStep, 0.0f));
            selectedDrawable->setTransformation(trans);
            std::cout << "Translated +Y" << std::endl;
        } else {
            Transformation trans = selectedDrawable->getTransformation();
            trans.rotate(rotationStep, glm::vec3(0.0f, 1.0f, 0.0f));
            selectedDrawable->setTransformation(trans);
            std::cout << "Rotated +Y" << std::endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        if (!rotationEnabled){
            Transformation trans = selectedDrawable->getTransformation();
            trans.translate(glm::vec3(0.0f, -translationStep, 0.0f));
            selectedDrawable->setTransformation(trans);
            std::cout << "Translated -Y" << std::endl;
        } else {
            Transformation trans = selectedDrawable->getTransformation();
            trans.rotate(-rotationStep, glm::vec3(0.0f, 1.0f, 0.0f));
            selectedDrawable->setTransformation(trans);
            std::cout << "Rotated +Y" << std::endl;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        if (!rotationEnabled){
            Transformation trans = selectedDrawable->getTransformation();
            trans.translate(glm::vec3(0.0f, 0.0f, translationStep));
            selectedDrawable->setTransformation(trans);
            std::cout << "Translated +Z" << std::endl;
        } else {
            Transformation trans = selectedDrawable->getTransformation();
            trans.rotate(rotationStep, glm::vec3(0.0f, 0.0f, 1.0f));
            selectedDrawable->setTransformation(trans);
            std::cout << "Rotated +Z" << std::endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        if (!rotationEnabled){
            Transformation trans = selectedDrawable->getTransformation();
            trans.translate(glm::vec3(0.0f, 0.0f, -translationStep));
            selectedDrawable->setTransformation(trans);
            std::cout << "Translated -Z" << std::endl;
        } else {
            Transformation trans = selectedDrawable->getTransformation();
            trans.rotate(-rotationStep, glm::vec3(0.0f, 0.0f, 1.0f));
            selectedDrawable->setTransformation(trans);
            std::cout << "Rotated -Z" << std::endl;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        Transformation trans = selectedDrawable->getTransformation();
        trans.scale(glm::vec3(1.0f + scaleStep));
        selectedDrawable->setTransformation(trans);
        std::cout << "Scaled Up" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        Transformation trans = selectedDrawable->getTransformation();
        trans.scale(glm::vec3(1.0f - scaleStep));
        selectedDrawable->setTransformation(trans);
        std::cout << "Scaled Down" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        rotationEnabled = !rotationEnabled;
        std::cout << "Rotation: " << rotationEnabled << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        selectedDrawableIndex = (selectedDrawableIndex + 1) % drawables.size();
        std::cout << "Switched to Drawable Index: " << selectedDrawableIndex << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        switchScene(0);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        switchScene(1);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        switchScene(2);
    }
}

void Application::switchScene(int index)
{
    if (index >=0 && index < scenes.size()) {
        currentSceneIndex = index;
        selectedDrawableIndex = 0;
        std::cout << "Switched to Scene Index: " << currentSceneIndex + 1 << std::endl;
    } else {
        std::cerr << "Invalid scene index: " << index << std::endl;
    }
}