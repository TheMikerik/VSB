// Controller.cpp
#include "Controller.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "Transformation.h"

// Static instance pointer for callbacks
static Controller* controllerInstance = nullptr;

// Callback implementations
void Controller::errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

void Controller::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Controller::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (controllerInstance) {
        if (controllerInstance->firstMouse) {
            controllerInstance->lastX = static_cast<float>(xpos);
            controllerInstance->lastY = static_cast<float>(ypos);
            controllerInstance->firstMouse = false;
        }

        float xoffset = static_cast<float>(xpos) - controllerInstance->lastX;
        float yoffset = controllerInstance->lastY - static_cast<float>(ypos); // reversed since y-coordinates go from bottom to top

        controllerInstance->lastX = static_cast<float>(xpos);
        controllerInstance->lastY = static_cast<float>(ypos);

        controllerInstance->camera.ProcessMouseMovement(xoffset, yoffset);
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
      lastX(400.0f), lastY(300.0f), firstMouse(true),
      deltaTime(0.0f), lastFrame(0.0f)
{
    // Set the static instance pointer for callbacks
    controllerInstance = this;

    // Set GLFW callbacks to the Controller's callbacks
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

void Controller::handleInput(float deltaTimeInput, int& currentSceneIndex) {
    currentSceneIndex = this->currentSceneIndex;
    deltaTime = deltaTimeInput - lastFrame;
    lastFrame = deltaTimeInput;
    processKeyboardInput(deltaTime);
    processTransformationInput();
}

void Controller::switchScene(int index){
    if (index >=0 && index < static_cast<int>(scenes.size())) {
        currentSceneIndex = index;
        selectedDrawableIndex = 0;
        std::cout << "Switched to Scene Index: " << currentSceneIndex << std::endl;
    } else {
        std::cerr << "Invalid scene index: " << index << std::endl;
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

    // Scene switching
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        switchScene(0);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        switchScene(1);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        switchScene(2);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        switchScene(3);
    }

    static bool spacePressedLastFrame = false;
    bool spacePressedThisFrame = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;

    if (spacePressedThisFrame && !spacePressedLastFrame) {
        if (currentSceneIndex >= 0 && currentSceneIndex < static_cast<int>(scenes.size())) {
            scenes[currentSceneIndex]->switchShader();
        }
    }

    spacePressedLastFrame = spacePressedThisFrame;
}

void Controller::processTransformationInput() {
    if (scenes.empty()) return;

    auto& currentScene = scenes[currentSceneIndex]; // Adjust based on your scene management
    if (!currentScene) return;

    auto& drawables = currentScene->getDrawables();
    if (drawables.empty()) return;

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
            std::cout << "Rotated -Y" << std::endl;
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