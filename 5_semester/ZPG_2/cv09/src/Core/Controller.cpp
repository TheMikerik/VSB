// Controller.cpp
#include "Core/Controller.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "Core/Transformation.h"
#include "Scenes/Scene6.h"
#include "Core/Transformation/TranslateOperation.h"
#include "Core/Transformation/RotateOperation.h"
#include "Core/Transformation/ScaleOperation.h"
#include <glm/gtc/matrix_transform.hpp>

static Controller* controllerInstance = nullptr;

void Controller::errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

void Controller::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Controller::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (controllerInstance) {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            if (controllerInstance->firstMouse) {
                controllerInstance->lastX = static_cast<float>(xpos);
                controllerInstance->lastY = static_cast<float>(ypos);
                controllerInstance->firstMouse = false;
            }

            float xoffset = static_cast<float>(xpos) - controllerInstance->lastX;
            float yoffset = controllerInstance->lastY - static_cast<float>(ypos);

            controllerInstance->lastX = static_cast<float>(xpos);
            controllerInstance->lastY = static_cast<float>(ypos);

            controllerInstance->camera.ProcessMouseMovement(xoffset, yoffset);
        }
    }
}

void Controller::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (controllerInstance && action == GLFW_PRESS) {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                controllerInstance->handleMouseClick(xpos, ypos);
            } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                controllerInstance->handleMouseClickSpawn(xpos, ypos);
            }
        }
    }
}

void Controller::handleMouseClickSpawn(double xpos, double ypos) {
    int windowWidth, windowHeight;
    int framebufferWidth, framebufferHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    
    float scaleX = (float)framebufferWidth / (float)windowWidth;
    float scaleY = (float)framebufferHeight / (float)windowHeight;
    
    GLint x = static_cast<GLint>(xpos * scaleX);
    GLint y = static_cast<GLint>(ypos * scaleY);
    
    GLint newY = framebufferHeight - y;
    
    GLfloat depth;
    glReadPixels(x, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();
    glm::vec4 viewport = glm::vec4(0, 0, framebufferWidth, framebufferHeight);
    
    glm::vec3 screenCoords = glm::vec3(x, newY, depth);
    
    glm::vec3 worldPos = glm::unProject(screenCoords, view, projection, viewport);
    
    std::cout << "\n=== SPAWN OBJECT ===" << std::endl;
    std::cout << "Screen coords: (" << xpos << ", " << ypos << ")" << std::endl;
    std::cout << "Framebuffer coords: (" << x << ", " << newY << ")" << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << "World position: (" << worldPos.x << ", " << worldPos.y << ", " << worldPos.z << ")" << std::endl;
    std::cout << "==================\n" << std::endl;
    
    if (currentSceneIndex >= 0 && currentSceneIndex < static_cast<int>(scenes.size())) {
        scenes[currentSceneIndex]->spawnObjectAtPosition(worldPos);
    }
}

void Controller::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (controllerInstance) {
        controllerInstance->camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }
}

Controller::Controller(GLFWwindow* win, Camera& cam, std::vector<std::shared_ptr<Scene>>& scns)
    : window(win), camera(cam), scenes(scns),
      selectedDrawableIndex(0), rotationEnabled(false),
      lastX(400.0f), lastY(300.0f), firstMouse(true)
{
    controllerInstance = this;

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void Controller::handleInput(float deltaTimeInput, int& currentSceneIndex) {
    currentSceneIndex = this->currentSceneIndex;
    processKeyboardInput(deltaTimeInput);
}

void Controller::switchScene(int index){
    if (index >=0 && index < static_cast<int>(scenes.size())) {
        currentSceneIndex = index;
        selectedDrawableIndex = 0;
        std::cout << "Scene: " << currentSceneIndex + 1 << std::endl;
    } else {
        std::cerr << "Invalid scene index: " << index << std::endl;
    }
}

void Controller::handleMouseClick(double xpos, double ypos) {
    int windowWidth, windowHeight;
    int framebufferWidth, framebufferHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    
    float scaleX = (float)framebufferWidth / (float)windowWidth;
    float scaleY = (float)framebufferHeight / (float)windowHeight;
    
    GLint x = static_cast<GLint>(xpos * scaleX);
    GLint y = static_cast<GLint>(ypos * scaleY);
    
    GLint newY = framebufferHeight - y;
    
    GLbyte color[4];
    GLfloat depth;
    GLuint index;
    
    glReadPixels(x, newY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
    
    std::cout << "Clicked on pixel (" << xpos << ", " << ypos << ") -> framebuffer (" << x << ", " << newY << ")" << std::endl;
    std::cout << "  Scale: " << scaleX << "x" << scaleY << std::endl;
    std::cout << "  Color: " << std::hex << (int)color[0] << (int)color[1] 
              << (int)color[2] << (int)color[3] << std::dec << std::endl;
    std::cout << "  Depth: " << depth << std::endl;
    std::cout << "  Stencil index: " << index << std::endl;
    
    if (currentSceneIndex >= 0 && currentSceneIndex < static_cast<int>(scenes.size())) {
        if (index > 0) {
            scenes[currentSceneIndex]->selectObject(index);
        } else {
            scenes[currentSceneIndex]->deselectAll();
            std::cout << "Clicked on background" << std::endl;
        }
    }
}

void Controller::processKeyboardInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime * 3);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime * 3);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime * 3);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime * 3);


    static bool sceneKeyPressedLastFrame[4] = {false, false, false, false};

    bool sceneKey1PressedThisFrame = glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS;
    bool sceneKey2PressedThisFrame = glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS;
    bool sceneKey3PressedThisFrame = glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS;
    bool sceneKey4PressedThisFrame = glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS;

    if (sceneKey1PressedThisFrame && !sceneKeyPressedLastFrame[0]) switchScene(0);
    if (sceneKey2PressedThisFrame && !sceneKeyPressedLastFrame[1]) switchScene(1);
    if (sceneKey3PressedThisFrame && !sceneKeyPressedLastFrame[2]) switchScene(2);
    if (sceneKey4PressedThisFrame && !sceneKeyPressedLastFrame[3]) switchScene(3);

    sceneKeyPressedLastFrame[0] = sceneKey1PressedThisFrame;
    sceneKeyPressedLastFrame[1] = sceneKey2PressedThisFrame;
    sceneKeyPressedLastFrame[2] = sceneKey3PressedThisFrame;
    sceneKeyPressedLastFrame[3] = sceneKey4PressedThisFrame;



    static bool spacePressedLastFrame = false;
    bool spacePressedThisFrame = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;

    if (spacePressedThisFrame && !spacePressedLastFrame) {
        if (currentSceneIndex >= 0 && currentSceneIndex < static_cast<int>(scenes.size())) {
            scenes[currentSceneIndex]->switchShader();
        }
    }

    static bool cPressedLastFrame = false;
    bool lPressedThisFrame = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;
    
    if (lPressedThisFrame && !cPressedLastFrame) {
        bool cursorEnabled = glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
        glfwSetInputMode(window, GLFW_CURSOR, cursorEnabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        firstMouse = true;
    }

    static bool fPressedLastFrame = false;
    bool fPressedThisFrame = glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS;
    
    if (fPressedThisFrame && !fPressedLastFrame) {
        if (currentSceneIndex >= 0 && currentSceneIndex < static_cast<int>(scenes.size())) {
            auto scene6 = std::dynamic_pointer_cast<Scene6>(scenes[currentSceneIndex]);
            if (scene6) {
                scene6->toggleFlashlight();
            }
        }
    }

    static bool deletePressedLastFrame = false;
    bool deletePressedThisFrame = glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS;
    
    if (deletePressedThisFrame && !deletePressedLastFrame) {
        if (currentSceneIndex >= 0 && currentSceneIndex < static_cast<int>(scenes.size())) {
            scenes[currentSceneIndex]->deleteSelected();
        }
    }

    cPressedLastFrame = lPressedThisFrame;
    spacePressedLastFrame = spacePressedThisFrame;
    fPressedLastFrame = fPressedThisFrame;
    deletePressedLastFrame = deletePressedThisFrame;
}

void Controller::setSelectedDrawable(size_t index) {
    if (index < scenes.size()) {
        selectedDrawableIndex = index;
    }
}

void Controller::setRotationEnabled(bool enabled) {
    rotationEnabled = enabled;
}

bool Controller::isRotationEnabled() const {
    return rotationEnabled;
}