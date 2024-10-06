#include "Application.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Definice cesty k shaderům
#define SHADER_DIR "shaders/"

// Callback funkce pro chyby
void Application::error_callback(int error, const char* description) {
    std::cerr << "Error (" << error << "): " << description << std::endl;
}

Application::Application()
    : window(nullptr), shaderProgram(nullptr),
      Projection(glm::mat4(1.0f)),
      View(glm::mat4(1.0f)),
      ModelMatrix(glm::mat4(1.0f)) {}

Application::~Application() {
    for(auto model : models) {
        delete model;
    }
    delete shaderProgram;
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

    // Nastavení OpenGL kontextu
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pro macOS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window){
        std::cerr << "ERROR: Could not create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Inicializace GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR: Could not initialize GLEW" << std::endl;
        return false;
    }

    // Zobrazení informací o OpenGL
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Získání velikosti framebufferu a nastavení viewportu
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Nastavení ortografické projekce pro 2D
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    float orthoLeft = -aspect;
    float orthoRight = aspect;
    float orthoBottom = -1.0f;
    float orthoTop = 1.0f;

    Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, -1.0f, 1.0f);

    // Nastavení View matrix na identitu pro 2D
    View = glm::mat4(1.0f);

    // Povolení blendingu pro průhlednost, pokud je potřeba
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Povolení depth testu pro 3D objekty
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return true;
}

void Application::createShaders() {
    std::string vertexPath = std::string(SHADER_DIR) + "vertex_shader.glsl";
    std::string fragmentPath = std::string(SHADER_DIR) + "fragment_shader.glsl";
    
    shaderProgram = new Shader(vertexPath, fragmentPath);
}

void Application::createModels() {
    // Vytvoření trojúhelníku
    Triangle* triangle = new Triangle();
    models.push_back(triangle);
    modelMatrices.push_back(glm::mat4(1.0f)); // Žádná transformace

    // Vytvoření čtverce
    Square* square = new Square();
    models.push_back(square);
    modelMatrices.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f))); // Posunutí doleva

    // Vytvoření krychle
    Cube* cube = new Cube();
    models.push_back(cube);
    modelMatrices.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, -1.0f))); // Posunutí dopředu
    
    // Vytvoření dalších modelů dle potřeby
}

void Application::run() {
    while (!glfwWindowShouldClose(window)){
        // Vyčistit obrazovku s využitím hloubkového bufferu
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Aktivovat shader program
        shaderProgram->use();

        // Pro každý model nastavíme MVP matici a vykreslíme ho
        for(size_t i = 0; i < models.size(); ++i){
            glm::mat4 MVP = Projection * View * modelMatrices[i];
            shaderProgram->setMat4("MVP", MVP);
            models[i]->draw();
        }

        // Zpracovat události a vyměnit buffer
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}