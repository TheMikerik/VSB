#include "Core/Application.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Model.h"
#include "Core/Controller.h"
#include "Graphics/DrawableObject.h"
#include "Core/Transformation.h"
#include "Interfaces/ICameraObserver.h"

#include "Scenes/Scene1.h"
#include "Scenes/Scene3.h"
#include "Scenes/Scene5.h"
#include "Scenes/Scene6.h"
#include "Scenes/Scene7.h"
#include "Scenes/Scene8.h"

#include <iostream>
#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <thread>

Application App;

Application::Application()
    : window(nullptr), currentSceneIndex(0),
      camera(glm::vec3(0.0f, 10.0f, 20.0f)),
      pointLight(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(1.0f))
{
}

Application::~Application()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initialization()
{
    glfwSetErrorCallback(Controller::errorCallback);
    if (!glfwInit()) {
        std::cerr << "ERROR: could not start GLFW3" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(1450, 900, "ZPG - RUC0066", nullptr, nullptr);
    if (!window) {
        std::cerr << "ERROR: could not create GLFW window" << std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
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

    controller = std::unique_ptr<Controller>(new Controller(window, camera, scenes));


    std::vector<std::string> faces = {
        "./images/posx.jpg",
        "./images/negx.jpg",
        "./images/posy.jpg",
        "./images/negy.jpg",
        "./images/posz.jpg",
        "./images/negz.jpg"
    };
    skybox = std::make_unique<Skybox>(faces);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::createScenes()
{
    auto scene1 = std::make_shared<Scene1>(camera);
    auto scene3 = std::make_shared<Scene3>(camera);
    auto scene5 = std::make_shared<Scene5>(camera);
    auto scene6 = std::make_shared<Scene6>(camera);
    auto scene7 = std::make_shared<Scene7>(camera);
    auto scene8 = std::make_shared<Scene8>(camera);

    scenes.emplace_back(scene1);
    scenes.emplace_back(scene3);
    scenes.emplace_back(scene5);
    scenes.emplace_back(scene6);
    scenes.emplace_back(scene7);
    scenes.emplace_back(scene8);
}

void Application::run()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float lastFrameTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrameTime;
        lastFrameTime = currentFrame;

        if (currentSceneIndex >= 0 && currentSceneIndex < scenes.size()) {
            const glm::vec4& bgColor = scenes[currentSceneIndex]->getBackgroundColor();
            glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (currentSceneIndex >= 0 && currentSceneIndex < scenes.size()) {
            scenes[currentSceneIndex]->render(deltaTime);
        }


        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix();
        // skybox->render(view, projection);

        glfwSwapBuffers(window);
        glfwPollEvents();

        controller->handleInput(deltaTime, currentSceneIndex);
    }

    glDisable(GL_DEPTH_TEST);
}