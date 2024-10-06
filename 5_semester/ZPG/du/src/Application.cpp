#include "Application.h"
#include <iostream>

// Define shader directory path
#define SHADER_DIR "shaders/"

// Error callback function
void Application::error_callback(int error, const char* description) {
    std::cerr << "Error (" << error << "): " << description << std::endl;
}

Application::Application()
    : window(nullptr), shaderProgram(nullptr), model(nullptr),
      Projection(glm::mat4(1.0f)), // Will be set in initialization
      View(glm::mat4(1.0f)),        // Identity matrix for 2D
      ModelMatrix(glm::mat4(1.0f)) {}
      // Alternatively, set Projection in initialization()

Application::~Application() {
    delete shaderProgram;
    delete model;
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

bool Application::initialization() {
    glfwSetErrorCallback(Application::error_callback);
    if (!glfwInit()) {
        std::cerr << "ERROR: Could not start GLFW3" << std::endl;
        return false;
    }

    // Initialize OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window){
        std::cerr << "ERROR: Could not create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR: Could not initialize GLEW" << std::endl;
        return false;
    }

    // Print OpenGL info
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Get framebuffer size and set viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Setup Orthographic Projection
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    float orthoLeft = -aspect;
    float orthoRight = aspect;
    float orthoBottom = -1.0f;
    float orthoTop = 1.0f;

    Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, -1.0f, 1.0f);

    // Set View Matrix to Identity for 2D
    View = glm::mat4(1.0f);

    // Enable blending for transparency if needed
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Application::createShaders() {
    std::string vertexPath = SHADER_DIR "vertex_shader.glsl";
    std::string fragmentPath = SHADER_DIR "fragment_shader.glsl";
    
    shaderProgram = new Shader(vertexPath, fragmentPath);
}

void Application::createModels() {
    // Define vertices for a square (two triangles)
    float vertices[] = {
        -0.5f,  0.5f, 0.0f, // Top-left
         0.5f,  0.5f, 0.0f, // Top-right
         0.5f, -0.5f, 0.0f, // Bottom-right
         0.5f, -0.5f, 0.0f, // Bottom-right
        -0.5f, -0.5f, 0.0f, // Bottom-left
        -0.5f,  0.5f, 0.0f  // Top-left
    };
    model = new Model(vertices, sizeof(vertices));
}

void Application::run() {
    while (!glfwWindowShouldClose(window)){
        // Clear the screen with a dark background
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // No need for depth buffer in 2D

        // Use shader program
        shaderProgram->use();

        // Create MVP matrix
        glm::mat4 MVP = Projection * View * ModelMatrix;
        shaderProgram->setMat4("MVP", MVP);

        // Render the model
        model->draw();

        // Poll events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}